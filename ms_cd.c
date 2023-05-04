/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rficht <robin.ficht@free.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 12:02:02 by rficht            #+#    #+#             */
/*   Updated: 2023/05/04 16:48:37 by rficht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"

int	ms_cd(t_cmd cmd)
{
	if (!cmd.args[0])
	{
		printf("cd received empty arg\n");
		return (1);
	}
	cmd.args++;
	if (!cmd.args[0])
	{
		printf("cd needs a path to work\n");
		return (1);
	}
	if (chdir(cmd.args[0]) == -1)
		return (1);
	return (0);
}
