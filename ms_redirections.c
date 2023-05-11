/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdjemaa <mdjemaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 12:18:24 by mdjemaa           #+#    #+#             */
/*   Updated: 2023/05/11 16:06:37 by mdjemaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"

int	ms_get_fds(t_prog *ms)
{
	int	i;

	i = -1;
	while (++i < ms->nbcmd)
	{
		if (!ms_get_fdin(&(ms->cmd[i])) || !ms_get_fdout(&(ms->cmd[i])))
			return (FALSE);
		printf("commande 'pure' %s\n", ms->cmd[i].line);
	}
	return (TRUE);
}

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
	if (!ft_dollar_replace(cmd->filein))
		return (0);
	ft_trimquotes(cmd->filein);
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
	char	str[1000];

	ms_gof_init(&delstart, &append, &i, cmd);
	while (cmd->line[i] == ' ')
		i++;
	if (cmd->line[i] && ft_is_in(cmd->line[i], FORBID_REDIR) >= 0)
		return (0);
	start = i;
	while (cmd->line[i] && ft_is_in(cmd->line[i], END_REDIR) == -1)
		i++;
	cmd->fileout = ft_substr(cmd->line, start, i - start);
	// ft_trimquotes(ft_dollar_replace(cmd->fileout));
	if (append)
	{
		cmd->fdout = open(cmd->fileout, O_CREAT | O_RDWR, 0644);
		while (read(cmd->fdout, &str, 1000))
			;
	}
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
