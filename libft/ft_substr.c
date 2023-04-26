/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdjemaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 14:53:52 by mdjemaa           #+#    #+#             */
/*   Updated: 2022/11/07 17:20:30 by mdjemaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*subs;
	size_t	size;
	size_t	i;

	if (!s || start >= ft_strlen(s))
	{
		subs = malloc(1);
		if (!subs)
			return (0);
		subs[0] = 0;
		return (subs);
	}
	size = ft_min(ft_strlen(s) - start, len);
	subs = malloc(size + 1);
	if (!subs)
		return (0);
	i = 0;
	while (i < size)
	{
		subs[i] = s[start + i];
		i++;
	}
	subs[i] = 0;
	return (subs);
}
