/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_crash.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rficht <robin.ficht@free.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 09:55:29 by rficht            #+#    #+#             */
/*   Updated: 2023/05/03 10:30:02 by rficht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"

void	ms_free(t_prog	*program)
{
	if (program)
	{
		if(program->cmd)
			{
				
			}
	}
		
}

void	ms_crash(t_prog *program)
{
	if (program)
		ms_free(program);
	perror("minishell : ");
}
