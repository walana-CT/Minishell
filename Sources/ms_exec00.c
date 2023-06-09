/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec00.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdjemaa <mdjemaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 20:28:47 by mdjemaa           #+#    #+#             */
/*   Updated: 2023/06/08 18:29:03 by mdjemaa          ###   ########.fr       */
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
			exit(1);
		if (access(cmd.filein, R_OK) == -1)
			exit(126);
	}
	if (cmd.fdout == -1)
	{
		if (access(cmd.filein, F_OK) == -1)
			exit(1);
		if (access(cmd.filein, W_OK) == -1)
			exit(126);
	}
	exit(1);
}

void	ms_check_perm_n_fds(t_cmd cmd)
{
	if (cmd.invalidfd)
		ms_exit_fd(cmd);
	if (ms_is_localfile(cmd.cmd_name) && access(cmd.cmd_name, X_OK))
		exit(ms_error_file(cmd.cmd_name, 'x'));
	if (opendir(cmd.cmd_name) && ms_is_localfile(cmd.cmd_name))
		ms_exit_dir(cmd);
}
