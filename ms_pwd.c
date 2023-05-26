/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdjemaa <mdjemaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 09:55:49 by rficht            #+#    #+#             */
/*   Updated: 2023/05/26 21:45:22 by mdjemaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"

int	ms_pwd(t_cmd *cmd)
{
	char	buffer[MAXPATHLEN + 1];
	char	*result;

	buffer[MAXPATHLEN] = 0;
	result = getcwd(buffer, MAXPATHLEN);
	if (!result)
		return (1);
	if (ft_putstr_fd(buffer, cmd->fdout) == -1)
		return (1);
	write(cmd->fdout, "\n", 1);
	return (0);
}
