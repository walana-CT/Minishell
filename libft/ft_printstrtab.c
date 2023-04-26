/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printstrtab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdjemaa <mdjemaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 13:32:06 by mdjemaa           #+#    #+#             */
/*   Updated: 2023/03/13 11:57:24 by mdjemaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_printstrtab(char **tab, char *titre)
{
	ft_printf(GREEN"- %s -\n"RESET, titre);
	while (tab && *tab)
	{
		ft_printf("%s\n", *tab);
		tab++;
	}
	ft_printf(GREEN"--- END ---\n"RESET);
}
