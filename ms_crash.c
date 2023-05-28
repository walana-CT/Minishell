/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_crash.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rficht <robin.ficht@free.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 09:55:29 by rficht            #+#    #+#             */
/*   Updated: 2023/05/28 14:52:17 by rficht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"

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

int	ms_error_msg_nofile(char *file, int err)
{
	write(2, "msh: ", 5);
	write(2, file, ft_sstrlen(file));
	write(2, NO_F"\n", 28);
	return (err);
}

int	ms_bad_child_ending(char *str)
{
	char	*error;

	error = ft_strmanyjoin("msh: ", str, ": command not found\n", 0);
	write(2, error, ft_strlen(error));
	free(error);
	exit(127);
}
