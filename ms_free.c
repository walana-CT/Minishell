/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdjemaa <mdjemaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 21:40:22 by mdjemaa           #+#    #+#             */
/*   Updated: 2023/05/23 18:37:45 by mdjemaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"

void	ms_pipes_close_free_null(t_ms *ms)
{
	int	i;

	i = -1;
	while (++i < ms->nbcmd - 1)
	{
		close(ms->pipe[i][0]);
		close(ms->pipe[i][1]);
		free(ms->pipe[i]);
		ms->pipe[i] = 0;
	}
	if (ms->pipe)
		free(ms->pipe);
	ms->pipe = 0;
}

void	ms_free_cmd(t_ms *ms)
{
	int	i;
	int	err;

	i = -1;
	while (++i < ms->nbcmd)
	{
		waitpid(ms->pid[i], &err, 0);
		if (ms->cmd[i].fdin != 0)
			close(ms->cmd[i].fdin);
		if (ms->cmd[i].fdout != 1)
			close(ms->cmd[i].fdout);
		if (ms->cmd[i].filein)
			ft_freenull((void **) &ms->cmd[i].filein);
		if (ms->cmd[i].fileout)
			ft_freenull((void **)&ms->cmd[i].fileout);
		if (ms->cmd[i].args && !ms_isbuiltin(ms->cmd[i].cmd_name))
			ft_freetab(ms->cmd[i].args);
		if (ms->cmd[i].line)
			ft_freestr(&(ms->cmd[i].line));
		ms->err = WEXITSTATUS(err);
	}
}

void	ms_loop_free(t_ms *ms)
{

	if (ms->pipe)
		ms_pipes_close_free_null(ms);
	if (ms->nbcmd)
	{
		ms_free_cmd(ms);
		ft_freenull((void **) &ms->cmd);
	}
	ms->nbcmd = 0;
}

void	ms_free(t_ms *ms)
{
	int	n;

	n = 0;
	printf("ms free called\n");
	if (ms->envp)
	{
		while (ms->envp[n])
			ft_freestr(&ms->envp[n++]);
	}
}
