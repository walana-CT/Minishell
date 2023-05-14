/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rficht <robin.ficht@free.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 11:03:52 by rficht            #+#    #+#             */
/*   Updated: 2023/05/14 15:01:25 by rficht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"

int	ms_exit(t_cmd *cmd)
{
	ms_terminal_reset(cmd->prog);
	if (!cmd->args[0])
	{
		printf("env exit 0 args\n");
		return (1);
	}
	ms_free(cmd->prog);
	exit(EXIT_SUCCESS);
}
