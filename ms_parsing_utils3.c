/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parsing_utils3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdjemaa <mdjemaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 15:12:47 by mdjemaa           #+#    #+#             */
/*   Updated: 2023/05/08 15:13:29 by mdjemaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"

// retourne la position de la premiere occurence de c dans str
int	ms_where_is(char c, char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == c && ms_quote_status(str, i))
			return (i);
	return (-1);
}
