/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rficht <robin.ficht@free.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 09:55:49 by rficht            #+#    #+#             */
/*   Updated: 2023/04/30 10:31:38 by rficht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"Includes/minishell.h"

int	pwd(t_cmd cmd)
{
	char	buffer[MAXPATHLEN + 1];
	char	*result;

	buffer[MAXPATHLEN] = 0;
	result = getcwd(buffer, MAXPATHLEN);
	if (!result)
		return (1);
	if (ft_putstr_fd(buffer, cmd.fdout) == -1)
		return (1);
	return (0);
}
