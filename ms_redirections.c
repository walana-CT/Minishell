/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rficht <robin.ficht@free.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 12:18:24 by mdjemaa           #+#    #+#             */
/*   Updated: 2023/05/19 14:43:05 by rficht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"

int	ms_getinfile(t_cmd *cmd, int i)
{
	int		delstart;
	int		start;

	delstart = i - 1;
	while (cmd->line[i] == ' ')
		i++;
	if (cmd->line[i] && ft_is_in(cmd->line[i], FORBID_REDIR) >= 0)
		return (0);
	start = i;
	while (cmd->line[i] && ft_is_in(cmd->line[i], END_REDIR) == -1)
		i++;
	cmd->filein = ft_substr(cmd->line, start, i - start);
	ft_strdelnfrom(cmd->line, delstart, i - delstart);
	if (dollar_replace(&cmd->filein, cmd->ms))
		return (0);
	ms_trimquotes(&cmd->filein);
	cmd->fdin = open(cmd->filein, O_RDONLY);
	return (1);
}

int	ms_get_fdin(t_cmd *cmd)
{
	int	i;
	int	del;

	del = 0;
	i = ms_where_is('<', cmd->line);
	while (i != -1)
	{
		if (cmd->filein)
			free(cmd->filein);
		if (cmd->line[i + 1] == '<')
		{
			if (!ms_get_limiter(cmd, i + 2))
				return (FALSE);
			ms_heredoc(*cmd);
		}
		else
			if (!ms_getinfile(cmd, i + 1) || cmd->fdin == -1)
				return (ms_error_msg_nofile(cmd->filein, FALSE));
		i = ms_where_is('<', cmd->line);
	}
	return (TRUE);
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

int	ms_getoutfile(t_cmd *cmd, int i)
{
	int		delstart;
	int		start;
	int		append;

	ms_gof_init(&delstart, &append, &i, cmd);
	while (cmd->line[i] == ' ')
		i++;
	if (cmd->line[i] && ft_is_in(cmd->line[i], FORBID_REDIR) >= 0)
		return (0);
	start = i;
	while (cmd->line[i] && ft_is_in(cmd->line[i], END_REDIR) == -1)
		i++;
	cmd->fileout = ft_substr(cmd->line, start, i - start);
	if (dollar_replace(&cmd->fileout, cmd->ms))
		return (0);
	ms_trimquotes(&cmd->fileout);
	if (append)
		cmd->fdout = ms_getappendfd(*cmd);
	else
		cmd->fdout = open(cmd->fileout, O_CREAT | O_RDWR | O_TRUNC, 0644);
	ft_strdelnfrom(cmd->line, delstart, i - delstart);
	return (1);
}

int	ms_get_fdout(t_cmd *cmd)
{
	int	i;
	int	del;

	del = 0;
	i = ms_where_is('>', cmd->line);
	while (i != -1)
	{
		if (cmd->fileout)
			free(cmd->fileout);
		if (!ms_getoutfile(cmd, i + 1) || cmd->fdout == -1)
			return (ms_error_msg_nofile(cmd->fileout, FALSE));
		i = ms_where_is('>', cmd->line);
	}
	return (TRUE);
}
