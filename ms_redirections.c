/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdjemaa <mdjemaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 12:18:24 by mdjemaa           #+#    #+#             */
/*   Updated: 2023/05/26 23:09:39 by mdjemaa          ###   ########.fr       */
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
		return (1);
	start = i;
	while (cmd->line[i] && ft_is_in(cmd->line[i], END_REDIR) == -1)
		i++;
	cmd->filein = ft_substr(cmd->line, start, i - start);
	ft_strdelnfrom(&cmd->line, delstart, i - delstart);
	if (ms_dollar_replace(&cmd->filein, cmd->ms))
		return (1);
	ms_trimquotes(&cmd->filein);
	cmd->fdin = open(cmd->filein, O_RDONLY);
	return (0);
}

/**
 * Verify the infile is valid and interpret it into a Filedescriptor.
 * @param cmd a cmd struct.
 * @return return 0 or 1 whether the format of filein is valid or not.
 */
int	ms_get_fdin(t_cmd *cmd)
{
	int	i;
	int	del;

	del = 0;
	i = ms_where_is('<', cmd->line);
	while (i != -1)
	{
		if (cmd->limiter)
			ft_freestr(&cmd->limiter);
		if (cmd->filein)
			ft_freenull((void *)cmd->filein);
		if (cmd->line[i + 1] == '<')
		{
			if (ms_get_limiter(cmd, i + 2))
				return (1);
			if (ms_heredoc(cmd))
				return (1);
		}
		else
			if (ms_getinfile(cmd, i + 1) || cmd->fdin == -1)
				return (ms_error_msg_nofile(cmd->filein, 1));
		i = ms_where_is('<', cmd->line);
	}
	return (0);
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
		return (1);
	start = i;
	while (cmd->line[i] && ft_is_in(cmd->line[i], END_REDIR) == -1)
		i++;
	cmd->fileout = ft_substr(cmd->line, start, i - start);
	if (!cmd->fileout)
		ms_crash(cmd->ms);
	if (ms_dollar_replace(&cmd->fileout, cmd->ms))
		return (1);
	ms_trimquotes(&cmd->fileout);
	if (append)
		cmd->fdout = ms_getappendfd(*cmd);
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
	i = ms_where_is('>', cmd->line);
	while (i != -1)
	{
		if (cmd->fileout)
			ft_freenull((void *)cmd->fileout);
		if (ms_getoutfile(cmd, i + 1) || cmd->fdout == -1)
			return (ms_error_msg_nofile(cmd->fileout, 1));
		i = ms_where_is('>', cmd->line);
	}
	return (0);
}
