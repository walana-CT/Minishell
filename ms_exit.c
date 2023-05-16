/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdjemaa <mdjemaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 11:03:52 by rficht            #+#    #+#             */
/*   Updated: 2023/05/15 16:43:29 by mdjemaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"

int	ms_exit(t_ms *ms)
{
	if (!ms || ms->nbcmd > 1)
		return (1);
	printf("exit\n");
	ms_free(ms);
	exit(EXIT_SUCCESS);
}
