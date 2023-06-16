/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_crash.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdjemaa <mdjemaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 09:55:29 by rficht            #+#    #+#             */
/*   Updated: 2023/06/16 17:09:11 by mdjemaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Free any memory in ms before to write err message and close.
 * This function is called after a system err and need erno to be correctly set.
 * @param ms address of minishell.
 */
void	ms_crash(t_ms *ms)
{
	if (ms)
		ms_free(ms);
	perror("msh : ");
	exit(errno);
}

int	ms_error_msg(char *str, int err)
{
	write(2, str, ft_sstrlen(str));
	write(2, "\n", 1);
	return (err);
}

int	ms_error_file(char *file, char m, int err)
{
	write(2, "msh: ", 5);
	write(2, file, ft_sstrlen(file));
	if (m == 'c')
		write(2, ": command not found\n", 20);
	else if (access(file, F_OK) == -1)
		write(2, NO_F"\n", 28);
	else if (m == 'w' && access(file, W_OK) == -1)
		write(2, ": Permission denied\n", 20);
	else if (m == 'r' && access(file, R_OK) == -1)
		write(2, ": Permission denied\n", 20);
	else if (m == 'x' && ((access(file, R_OK) == -1) || \
		(access(file, X_OK) == -1)))
		write(2, ": Permission denied\n", 20);
	return (err);
}

void	ms_bad_child_ending(char *str)
{
	DIR	*dirp;

	if (ft_strequal(str, ""))
		exit(0);
	if (ms_is_localfile(str) && access(str, F_OK) == -1)
		exit(ms_error_file(str, 'f', 127));
	if (ms_is_localfile(str) && access(str, X_OK) == -1)
		exit(ms_error_file(str, 'x', 126));
	dirp = opendir(str);
	if (ms_where_is('/', str) != -1 && dirp)
	{
		closedir(dirp);
		exit(ms_exit_dir(str));
	}
	exit(ms_error_file(str, 'c', 127));
}

int	ms_exit_dir(char *str)
{
	write(2, "msh: ", 5);
	write(2, str, ft_sstrlen(str));
	write(2, " : is a directory\n", 18);
	exit(126);
}
