/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdjemaa <mdjemaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 11:03:52 by rficht            #+#    #+#             */
/*   Updated: 2023/05/30 14:04:58 by mdjemaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"

//tputs
int	ms_exit(t_cmd *cmd)
{
	if (!cmd->args[0])
	{
		printf("exit received 0 args\n");
		return (1);
	}
	if (!cmd->args[1])
		ms_close(cmd->ms, 127);
	else if (cmd->args[2])
	{
		printf("exit : too many arguments\n");
		stat_err(1);
		return (1);
	}
	ms_close(cmd->ms, ft_atoi(cmd->args[1]));
	return (0);
}

int	ms_close(t_ms *ms, int val)
{
	printf("\033[1Fmsh > \033[0mexit\n");
	if (ms->cmd)
		printf("exit\n");
	ms_free(ms);
	system("leaks minishell");
	exit(val);
}
