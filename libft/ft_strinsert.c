/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strinsert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rficht <robin.ficht@free.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 16:45:28 by rficht            #+#    #+#             */
/*   Updated: 2023/05/17 10:13:39 by rficht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/libft.h"

//insert str2 dans str1 a l'index pos (free str1) si str2 NULL ne fait rieng
int	ft_strinsert(char **str1, char *str2, int pos)
{
	char	*result;
	int		i;
	int		j;

	/*printf("calling strinsert\n");
	printf("str 1 : %s\n", *str1);
	printf("str 2 : %s\n", str2);
	printf("pos : %d\n", pos);*/
	if (!str1)
		return (1);
	if (!(*str1))
		return (1);
	if (!(str2))
		return (0);
	i = -1;
	j = -1;
	if ((size_t) pos > ft_strlen(*str1))
		return (1);
	result = ft_calloc((ft_strlen(*str1) + ft_strlen(str2) + 1), sizeof(char));
	while (++i < pos)
		result[i] = (*str1)[i];
	while (str2[++j])
		result[i + j] = str2[j];
	while ((*str1)[i])
	{
		result[i + j] = (*str1)[i];
		i++;
	}
	free(*str1);
	*str1 = result;
	return (0);
}
