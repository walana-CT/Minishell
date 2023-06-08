/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec01.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdjemaa <mdjemaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:50:04 by mdjemaa           #+#    #+#             */
/*   Updated: 2023/06/08 17:50:45 by mdjemaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_child(t_ms *ms, int i)
{
	char	*pathcmd;

	ms_close_pipes_but(ms, i);
	ms_fixfds(&ms->cmd[i]);
	dup2(ms->cmd[i].fdin, 0);
	dup2(ms->cmd[i].fdout, 1);
	ms_check_perm_n_fds(ms->cmd[i]);
	if (ms_isbuiltin(ms->cmd[i].cmd_name))
		exit(ms_do_builtin(&ms->cmd[i]));
	else
	{
		if (!ms->cmd[i].path)
			pathcmd = ft_strdup(ms->cmd[i].cmd_name);
		else
			pathcmd = ft_strmanyjoin(ms->cmd[i].path, "/", \
				ms->cmd[i].cmd_name, 0);
		if (pathcmd && !ft_strequal(ms->cmd[i].cmd_name, ""))
			execve(pathcmd, ms->cmd[i].args, ms->envp);
		ft_freenull((void **)&pathcmd);
		ms_bad_child_ending(ms->cmd[i].cmd_name);
	}
}

int	ms_exec(t_ms *ms)
{
	int	i;
	int	err;

	if (ms->nbcmd == 1 && ms_isbuiltin(ms->cmd[0].cmd_name))
	{
		err = ms_do_builtin(&ms->cmd[0]);
		stat_err(err);
		return (0);
	}
	ms->pid = ft_calloc(ms->nbcmd, sizeof(int));
	if (!ms->pid)
		return (1);
	i = -1;
	stat_sig(disabled);
	while (++i < ms->nbcmd)
	{
		ms->pid[i] = fork();
		if (!ms->pid[i])
		{
			stat_sig(child);
			ms_child(ms, i);
		}
	}
	return (0);
}
