/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_crash.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdjemaa <mdjemaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 09:55:29 by rficht            #+#    #+#             */
/*   Updated: 2023/05/12 19:53:54 by mdjemaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"

void	ms_pipes_close_free_null(t_prog *ms)
{
	int	i;

	i = -1;
	while (ms->pipe[++i])
	{
		close(ms->pipe[i][0]);
		close(ms->pipe[i][1]);
		free(ms->pipe[i]);
		ms->pipe[i] = 0;
	}
	free(ms->pipe);
	ms->pipe = 0;
}

void	ms_free_cmd(t_prog *ms)
{
	int	i;

	i = -1;
	while (++i < ms->nbcmd)
	{
		if (ms->cmd[i].fdin != 0)
			close(ms->cmd[i].fdin);
		if (ms->cmd[i].fdout != 1)
			close(ms->cmd[i].fdout);
		if (ms->cmd[i].filein)
			ft_freenull((void **) &ms->cmd[i].filein);
		if (ms->cmd[i].fileout)
			ft_freenull((void **)&ms->cmd[i].fileout);
		ft_freetab(ms->cmd[i].args);
		ft_freestr(&(ms->cmd[i].line));
	}
}

void	ms_usual_free(t_prog *ms, char *str, char *tmp)
{
	ft_freestr(&str);
	ft_freestr(&tmp);
	if (ms->pipe)
		ms_pipes_close_free_null(ms);
	if (ms->nbcmd)
	{
		ms_free_cmd(ms);
		ft_freenull((void **) &ms->cmd);
	}
	ms->nbcmd = 0;
}

void	ms_free(t_prog *program)
{
	int	n;

	n = 0;
	printf("ms free called\n");
	if (program->envp)
	{
		while (program->envp[n])
			ft_freestr(&program->envp[n++]);
	}
}

void	ms_crash(t_prog *program)
{
	if (program)
		ms_free(program);
	perror("msh : ");
}

int	ms_error_msg(char *str, int err)
{
	write(2, str, ft_sstrlen(str));
	write(2, "\n", 1);
	return (err);
}

int	ms_error_msg_nofile(char *file, int err)
{
	write(2, "msh: ", 5);
	write(2, file, ft_sstrlen(file));
	write(2, NO_F"\n", 28);
	return (err);
}
