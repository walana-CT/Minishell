/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strfjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rficht <robin.ficht@free.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 15:22:56 by mdjemaa           #+#    #+#             */
/*   Updated: 2023/04/29 15:25:27 by rficht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/libft.h"

// CAUTION : s1 will be freed
// usage should only be str = ft_strfjoin(mallocated str, "more_str");
char	*ft_strfjoin(char *s1, char *s2)
{
	size_t	size;
	size_t	i;
	size_t	j;
	char	*s3;

	size = ft_sstrlen(s1) + ft_sstrlen(s2);
	s3 = malloc(size + 1);
	if (!s3)
		return (0);
	i = 0;
	j = 0;
	while (s1[j])
		s3[i++] = s1[j++];
	j = 0;
	if (s2)
		while (s2[j])
			s3[i++] = s2[j++];
	s3[i] = 0;
	free(s1);
	return (s3);
}
