/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec00.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rficht <robin.ficht@free.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 20:28:47 by mdjemaa           #+#    #+#             */
/*   Updated: 2023/06/10 15:31:19 by rficht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	ms_exit_fd(t_cmd cmd)
{
	if (cmd.fdin == -1)
	{
		if (access(cmd.filein, F_OK) == -1)
			return (ms_error_file(cmd.filein, 'r', 1));
		if (access(cmd.filein, R_OK) == -1)
			return (ms_error_file(cmd.filein, 'r', 1));
	}
	if (cmd.fdout == -1)
	{
		if (access(cmd.fileout, F_OK) == -1)
			return (ms_error_file(cmd.fileout, 'w', 1));
		if (access(cmd.fileout, W_OK) == -1)
			return (ms_error_file(cmd.fileout, 'w', 1));
	}
	return (1);
}

void	ms_exit_check_perm_n_fds(t_cmd cmd)
{
	int	err;

	err = ms_check_perm_n_fds(cmd);
	if (err)
		exit(err);
}

int	ms_check_perm_n_fds(t_cmd cmd)
{
	if (cmd.invalidfd)
		return (ms_exit_fd(cmd));
	// if (ms_is_localfile(cmd.cmd_name) && access(cmd.cmd_name, X_OK))
	// 	return (ms_error_file(cmd.cmd_name, 'x', 126));
	// if (opendir(cmd.cmd_name) && ms_is_localfile(cmd.cmd_name))
	// 	return (ms_exit_dir(cmd));
	return (0);
}
