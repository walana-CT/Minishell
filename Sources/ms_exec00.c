/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec00.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdjemaa <mdjemaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 20:28:47 by mdjemaa           #+#    #+#             */
/*   Updated: 2023/06/08 17:57:31 by mdjemaa          ###   ########.fr       */
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
