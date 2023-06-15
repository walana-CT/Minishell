/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redir_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdjemaa <mdjemaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 16:27:44 by mdjemaa           #+#    #+#             */
/*   Updated: 2023/06/15 17:11:50 by mdjemaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_is_heredoc(t_cmd *cmd)
{
	int	n;

	n = -1;
	while (cmd->line[++n])
	{
		if (cmd->line[n] == '<' && cmd->line[n + 1] == '<')
		{
			return (TRUE);
		}
	}
	return (FALSE);
}

int	ms_get_heredoc(t_cmd *cmd)
{
	int	n;

	n = -1;
	while (cmd->line[++n])
	{
		if (cmd->line[n] == '<' && cmd->line[n + 1] == '<')
		{
			if (cmd->limiter)
			{
				ft_freestr(&cmd->limiter);
				cmd->limiter = NULL;
			}
			if (ms_get_limiter(cmd, n + 2))
				return (1);
			if (ms_heredoc(cmd))
				return (1);
		}
	}
	return (0);
}

void	ms_heredoc_child(t_cmd *cmd)
{
	char	*str;

	stat_sig(child);
	str = readline(">");
	while (!ft_strequal(cmd->limiter, str) && str)
	{
		if (!ms_dollar_replace(&str, cmd->ms))
		{
			write(cmd->herepipe[1], str, ft_sstrlen(str));
			write(cmd->herepipe[1], "\n", 1);
		}
		free(str);
		str = readline(">");
	}
	close(cmd->herepipe[1]);
	exit(0);
}

int	ms_heredoc(t_cmd *cmd)
{
	int		pid;
	int		err;

	err = 0;
	cmd->herepipe = malloc(2 * sizeof(int));
	if (!cmd->herepipe || pipe(cmd->herepipe) == -1)
		return (1);
	stat_sig(disabled);
	pid = fork();
	if (!pid)
		ms_heredoc_child(cmd);
	waitpid(pid, &err, 0);
	stat_sig(normal);
	close(cmd->herepipe[1]);
	cmd->fdin = cmd->herepipe[0];
	ft_freestr(&cmd->limiter);
	free(cmd->herepipe);
	cmd->herepipe = 0;
	return (WEXITSTATUS(err));
}
