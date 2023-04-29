/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_util_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rficht <robin.ficht@free.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 18:28:40 by mdjemaa           #+#    #+#             */
/*   Updated: 2023/04/29 17:35:46 by rficht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Includes/pipex_bonus.h"

void	px_close_pipes_but(t_pipex *p, int i)
{
	int	j;

	j = -1;
	while (++j < p->ncmds)
	{
		if (j != i)
			close(p->pipe[j][0]);
		if (j != i + 1)
			close(p->pipe[j][1]);
	}
}

void	px_first_child(t_pipex *p, int i, char **envp)
{
	px_close_pipes_but(p, i);
	dup2(p->pipe[0][0], 0);
	dup2(p->pipe[1][1], 1);
	execve(p->cmd[0], p->args[0], envp);
	px_bad_child_ending(p->cmd[0]);
}

void	px_child(t_pipex *p, int i, char **envp)
{
	px_close_pipes_but(p, i);
	dup2(p->pipe[i][0], 0);
	dup2(p->pipe[i + 1][1], 1);
	execve(p->cmd[i], p->args[i], envp);
	px_bad_child_ending(p->cmd[i]);
}

void	px_last_child(t_pipex *p, int i, char **envp)
{
	px_close_pipes_but(p, i);
	px_get_outfile(p);
	dup2(p->pipe[i][0], 0);
	dup2(p->pipe[p->ncmds - 1][1], 1);
	execve(p->cmd[i], p->args[i], envp);
	px_bad_child_ending(p->cmd[i]);
}

int	px_launch_children(t_pipex *p, char **envp)
{
	int	i;

	i = 0;
	p->pid[i] = fork();
	if (!p->pid[i])
		px_first_child(p, i, envp);
	while (++i < p->ncmds - 1)
	{
		p->pid[i] = fork();
		if (!p->pid[i])
			px_child(p, i, envp);
	}
	p->pid[i] = fork();
	if (!p->pid[i])
		px_last_child(p, i, envp);
	return (px_end_bonus(p));
}
