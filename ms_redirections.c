/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdjemaa <mdjemaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 12:18:24 by mdjemaa           #+#    #+#             */
/*   Updated: 2023/05/08 15:13:39 by mdjemaa          ###   ########.fr       */
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
	}
	return (TRUE);
}

int	ms_get_fdin(t_cmd *cmd)
{
	int	i;
	int	heredoc;

	cmd->fdin = 0;
	heredoc = 0;
	i = ms_where_is('<', cmd->line);
	while (i != -1)
	{
		if (cmd->line[i + 1] == '<')
			heredoc = 1;
	}
}

int	ms_get_fdout(t_cmd *cmd)
{
	return (TRUE);
}
