/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redir_outfile.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdjemaa <mdjemaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 17:08:47 by mdjemaa           #+#    #+#             */
/*   Updated: 2023/06/09 13:45:00 by mdjemaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_getoutfile(t_cmd *cmd, int i)
{
	int		delstart;
	int		start;
	int		append;

	ms_gof_init(&delstart, &append, &i, cmd);
	while (cmd->line[i] == ' ')
		i++;
	if (cmd->line[i] && ft_is_in(cmd->line[i], FORBID_REDIR) >= 0)
		return (1);
	start = i;
	while (cmd->line[i] && ft_is_in(cmd->line[i], END_REDIR) == -1)
		i = set_end_filename(cmd, i);
	cmd->fileout = ft_substr(cmd->line, start, i - start);
	if (!cmd->fileout)
		ms_crash(cmd->ms);
	if (ms_dollar_replace(&cmd->fileout, cmd->ms))
		return (1);
	ms_trimquotes(&cmd->fileout);
	if (append)
		cmd->fdout = open(cmd->fileout, O_CREAT | O_RDWR | O_APPEND, 0644);
	else
		cmd->fdout = open(cmd->fileout, O_CREAT | O_RDWR | O_TRUNC, 0644);
	ft_strdelnfrom(&cmd->line, delstart, i - delstart);
	return (0);
}

/**
 * Verify the outfile is valid and interpret it into a Filedescriptor.
 * @param cmd a cmd struct.
 * @return return 0 or 1 whether the format of filein is valid or not.
 */
int	ms_get_fdout(t_cmd *cmd)
{
	int	i;
	int	del;

	del = 0;
	while (ms_where_is('>', cmd->line) != -1)
	{
		i = ms_where_is('>', cmd->line);
		if (cmd->fileout)
			ft_freenull((void **)&cmd->fileout);
		if (ms_getoutfile(cmd, i + 1) || cmd->fdout == -1)
			return (1);
	}
	return (0);
}

/**
 * define the liniter if we encounter a << symbol.
 * @param cmd a struct cmd.
 * @param i index of char after the << symbol.
 * @return return 0 or 1 or whether if the Heredoc is valid or not. 
 */
int	ms_get_limiter(t_cmd *cmd, int i)
{
	int	delstart;
	int	start;

	delstart = i - 2;
	while (cmd->line[i] == ' ')
		i++;
	start = i;
	if (ft_is_in(cmd->line[i], FORBID_HEREDOC) >= 0)
		return (1);
	while (cmd->line[i] && ft_is_in(cmd->line[i], END_HEREDOC) == -1)
		i++;
	cmd->limiter = ft_substr(cmd->line, start, i - start);
	if (!cmd->limiter || !cmd->line)
		ms_crash(cmd->ms);
	ft_strdelnfrom(&cmd->line, delstart, i - delstart);
	ms_trimquotes(&cmd->limiter);
	if (!cmd->limiter)
		ms_crash(cmd->ms);
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
	free(cmd->limiter);
	free(cmd->herepipe);
	return (WEXITSTATUS(err));
}
