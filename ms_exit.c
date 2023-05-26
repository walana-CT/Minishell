/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rficht <robin.ficht@free.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 11:03:52 by rficht            #+#    #+#             */
/*   Updated: 2023/05/26 17:15:27 by rficht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"

//tputs
int	ms_exit(t_ms *ms)
{
	printf("\033[1F\033[36;1mmsh > \033[0mexit\n");
	if (!ms || ms->nbcmd > 1)
		return (1);
	if (ms->cmd)
		printf("exit\n");
	ms_free(ms);
	//system("leaks minishell");
	exit(EXIT_SUCCESS);
}
