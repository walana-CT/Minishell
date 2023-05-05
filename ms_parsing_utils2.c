/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parsing_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdjemaa <mdjemaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 09:32:57 by mdjemaa           #+#    #+#             */
/*   Updated: 2023/05/05 12:48:36 by mdjemaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"

int	ms_strstr(char *stack, char *hay)
{
	int	i;
	int	j;


	while (stack[i])
	{}
}

// liste de caracteres interdits apres un pipe
int	ms_forbiddenchar(char c)
{
	if (c == '\\' || c == ';')
		return (TRUE);
	return (FALSE);
}
