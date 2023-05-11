/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parsing_utils3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdjemaa <mdjemaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 15:12:47 by mdjemaa           #+#    #+#             */
/*   Updated: 2023/05/11 16:14:36 by mdjemaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"

void	ms_trimquotes(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		while (str[i] && (str[i] == '\'' || str[i] == '\"'))
			ft_strdelchar(str, i);
	}
}
