/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdjemaa <mdjemaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 11:03:52 by rficht            #+#    #+#             */
/*   Updated: 2023/05/31 14:33:04 by mdjemaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"

//tputs
int	ms_exit(t_cmd *cmd)
{
	int	return_val;

	printf("\033[1Fmsh > \033[0mexit\n");
	if (!cmd)
	{
		system("leaks minishell");
		exit(127);
	}
	printf("exit\n");
	if (!cmd->args[0])
		return (printf("exit received 0 args\n"), 1);
	if (!cmd->args[1])
		return_val = 127;
	else
	{
		return_val = ft_atoi(cmd->args[1]);
		if (cmd->args[2])
			return (printf("exit : too many arguments\n"), 1);
	}
	ms_free(cmd->ms);
	system("leaks minishell");
	exit(return_val);
	return (0);
}

