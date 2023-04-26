/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdjemaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 16:55:04 by mdjemaa           #+#    #+#             */
/*   Updated: 2022/11/04 12:27:24 by mdjemaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc( size_t count, size_t size )
{
	unsigned char	*str;
	size_t			t_size;

	t_size = count * size;
	str = malloc(t_size);
	if (!str)
		return (0);
	while (t_size--)
		str[t_size] = 0;
	return (str);
}
