/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdjemaa <mdjemaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 20:28:47 by mdjemaa           #+#    #+#             */
/*   Updated: 2023/06/07 16:08:55 by mdjemaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_do_builtin(t_cmd	*cmd)
{
	if (cmd->fdin == -1 || cmd->fdout == -1)
		return (stat_err(1));
	if (ft_strequal(cmd->cmd_name, "cd"))
		return (ms_cd(cmd));
	if (ft_strequal(cmd->cmd_name, "echo"))
		return (ms_echo(cmd));
	if (ft_strequal(cmd->cmd_name, "env"))
		return (ms_env(cmd));
	if (ft_strequal(cmd->cmd_name, "exit"))
		return (ms_exit(cmd));
	if (ft_strequal(cmd->cmd_name, "export"))
		return (ms_export(cmd));
	if (ft_strequal(cmd->cmd_name, "pwd"))
		return (ms_pwd(cmd));
	if (ft_strequal(cmd->cmd_name, "unset"))
		return (ms_unset(cmd));
	return (1);
}

void	ms_fixfds(t_cmd	*cmd)
{
	int	i;

	i = cmd->nb;
	if (!cmd->filein && !cmd->limiter)
	{
		if (i == 0)
			cmd->fdin = 0;
		else
			cmd->fdin = cmd->ms->pipe[i - 1][0];
	}
	if (!cmd->fileout)
	{
		if (i == cmd->ms->nbcmd - 1)
			cmd->fdout = 1;
		else
			cmd->fdout = cmd->ms->pipe[i][1];
	}
}

void	ms_close_pipes_but(t_ms *ms, int i)
{
	int	j;

	j = -1;
	while (++j < ms->nbcmd - 1)
	{
		if (j != i - 1)
			close(ms->pipe[j][0]);
		if (j != i)
			close(ms->pipe[j][1]);
	}
}

int	ms_is_localfile(char *file)
{
	return (file[0] == '.' || file[0] == '/');
}

	// if (ms->cmd[i].fdin == -1 || ms->cmd[i].fdout == -1)
	// 	exit(1);
void	ms_check_perm_n_fds(t_cmd cmd)
{
	if (cmd.invalidfd)
		exit(1);
	if (ms_is_localfile(cmd.cmd_name) && access(cmd.cmd_name, X_OK))
		ms_error_file(cmd.cmd_name, 'x');
	if (opendir(cmd.cmd_name) && ms_is_localfile(cmd.cmd_name))
		ms_exit_dir(cmd);
}

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
