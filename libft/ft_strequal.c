/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdjemaa <mdjemaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 13:44:00 by mdjemaa           #+#    #+#             */
/*   Updated: 2023/03/16 15:30:37 by mdjemaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strequal(char *str1, char *str2)
{
	size_t	i;
	size_t	size;

	size = ft_sstrlen(str1);
	if (size != ft_sstrlen(str2))
		return (0);
	i = -1;
	while (++i < size)
		if (str1[i] != str2[i])
			return (0);
	return (1);
}
/*
int	main(int argc, char **argv)
{
	if (argc != 3)
		return (1);
	if (ft_strequal(argv[1], argv[2]))
		ft_printf("OK\n");
	else
		ft_printf("KO\n");
	return (0);
}
*/