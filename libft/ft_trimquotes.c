/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trimquotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdjemaa <mdjemaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 16:49:49 by mdjemaa           #+#    #+#             */
/*   Updated: 2023/05/11 11:37:15 by mdjemaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/libft.h"

// a tester avec readline parce que dans un main c'est galere !
void	ft_trimquotes(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		while (str[i] && (str[i] == '\'' || str[i] == '\"'))
			ft_strdelchar(str, i);
	}
}

/*
int	main(void)
{
	char	*str;

	str = ft_strdup("abc\"\"'''''''\"de\"fghijklmno\"pqrs\"t'u'v'w'x'y'z'");
	ft_trimquotes(str);
	ft_printf("%s\n", str);
	if (ft_strequal(str, "abcdefghijklmnopqrstuvwxyz"))
		ft_printf(GREEN"SUCCESS\n"RESET);
	return (0);
}
*/