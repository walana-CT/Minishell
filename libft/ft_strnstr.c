/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdjemaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 10:17:50 by mdjemaa           #+#    #+#             */
/*   Updated: 2022/11/07 17:19:38 by mdjemaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	char	*hay;
	char	*nee;

	i = 0;
	hay = (char *) haystack;
	nee = (char *) needle;
	if (!hay && !len)
		return (NULL);
	if (!*nee)
		return (hay);
	while (hay[i] && i < len)
	{
		j = 0;
		while (nee[j] == hay[i + j] && i + j < len)
		{
			if (!nee[j + 1])
				return (&hay[i]);
			j++;
		}
		i++;
	}
	return (0);
}
