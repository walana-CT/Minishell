/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rficht <robin.ficht@free.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 12:18:24 by mdjemaa           #+#    #+#             */
/*   Updated: 2023/06/15 15:08:32 by rficht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_heardoc(t_cmd *cmd)
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


int	ms_get_heardoc(t_cmd *cmd)
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


void	ms_get_next_fd(t_cmd *cmd)
{
	int	in;
	int	out;


	while ((ms_where_is('<', cmd->line) != -1 || \
		ms_where_is('>', cmd->line) != -1) && !cmd->invalidfd)
	{
		in = ms_where_is('<', cmd->line);
		out = ms_where_is('>', cmd->line);

		if (is_heardoc(cmd))
			ms_get_heardoc(cmd);
		else if ((in < out && in != -1) || out == -1)
		{
			if (ms_get_fdin(cmd))
				cmd->invalidfd = 1;
		}
		else if ((out < in && out != -1) || in == -1)
			if (ms_get_fdout(cmd))
				cmd->invalidfd = 1;
	}
}

void	ms_get_fds(t_ms *ms)
{
	int	i;

	i = -1;
	while (++i < ms->nbcmd)
		ms_get_next_fd(&ms->cmd[i]);
}

void	ms_gof_init(int *dels, int *app, int *i, t_cmd *cmd)
{
	*dels = *i - 1;
	*app = 0;
	if (cmd->line[*i] == '>')
	{
		*app = 1;
		(*i)++;
	}
}

int	set_end_filename(t_cmd *cmd, int i)
{
	char	quote;

	if (ms_isquote(cmd->line[i]))
	{
		quote = cmd->line[i++];
		while (cmd->line[i] != quote)
			i++;
	}
	i++;
	return (i);
}
