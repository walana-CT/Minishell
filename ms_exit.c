/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdjemaa <mdjemaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 11:03:52 by rficht            #+#    #+#             */
/*   Updated: 2023/05/22 12:19:36 by mdjemaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"

int	ms_exit(t_ms *ms)
{
	printf("\033[1F\033[36;1mmsh > \033[0mexit\n"); // oui
	if (!ms || ms->nbcmd > 1)
		return (1);
	printf("exit\n");
	ms_free(ms);
	exit(EXIT_SUCCESS);
}
