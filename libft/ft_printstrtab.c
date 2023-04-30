/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printstrtab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rficht <robin.ficht@free.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 13:32:06 by mdjemaa           #+#    #+#             */
/*   Updated: 2023/04/30 10:20:35 by rficht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/libft.h"

void	ft_printstrtab(char **str_tab, char *titre)
{
	ft_printf(GREEN"- %s -\n"RESET, titre);
	while (str_tab && *str_tab)
	{
		ft_printf("%s\n", *str_tab);
		str_tab++;
	}
	ft_printf(GREEN"--- END ---\n"RESET);
}
