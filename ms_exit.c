/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rficht <robin.ficht@free.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 11:03:52 by rficht            #+#    #+#             */
/*   Updated: 2023/05/28 15:09:52 by rficht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"

//tputs
int	ms_exit(t_ms *ms)
{
	printf("\033[1Fmsh > \033[0mexit\n");
	if (!ms || ms->nbcmd > 1)
		return (1);
	if (ms->cmd)
		printf("exit\n");
	ms_free(ms);
	// system("leaks minishell");
	exit(EXIT_SUCCESS);
}
