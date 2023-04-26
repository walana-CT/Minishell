/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strisdigit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdjemaa <mdjemaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 14:30:00 by mdjemaa           #+#    #+#             */
/*   Updated: 2023/01/11 14:46:06 by mdjemaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strisdigit(const char *str)
{
	int	i;
	int	size;

	if (!str || !*str)
		return (0);
	if (*str == '-' || *str == '+')
		str++;
	size = ft_sstrlen(str);
	if (!size)
		return (0);
	i = -1;
	while (++i < size)
		if (!ft_isdigit(str[i]))
			return (0);
	return (1);
}
