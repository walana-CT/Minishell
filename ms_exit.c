/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rficht <robin.ficht@free.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 11:03:52 by rficht            #+#    #+#             */
/*   Updated: 2023/05/22 10:06:17 by rficht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"

int	ms_exit(t_ms *ms)
{
	printf("\x1b[1F\033[36;1mmsh > \033[0mexit\n"); // oui
	if (!ms || ms->nbcmd > 1)
		return (1);
	printf("exit\n");
	ms_free(ms);
	exit(EXIT_SUCCESS);
}
