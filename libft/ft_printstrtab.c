/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printstrtab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rficht <robin.ficht@free.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 13:32:06 by mdjemaa           #+#    #+#             */
/*   Updated: 2023/04/29 15:25:27 by rficht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/libft.h"

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
