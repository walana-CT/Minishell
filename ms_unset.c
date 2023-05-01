/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rficht <robin.ficht@free.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 11:03:19 by rficht            #+#    #+#             */
/*   Updated: 2023/04/30 15:01:01 by rficht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"

void	unset_arg(char *arg)
{
	char	buffer
}

void	ms_unset(t_cmd cmd)
{
	if (!cmd.args[0])
	{
		printf("ms_unset received NULL args\n");
		return (1);
	}
	cmd.args++;
	while (cmd.args[0])
	{
		unset_arg(cmd.args[0]);
		cmd.args++;
	}
}
