/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_2lst_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdjemaa <mdjemaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 11:13:00 by mdjemaa           #+#    #+#             */
/*   Updated: 2023/02/02 12:11:48 by mdjemaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_2list	*ft_2lstlast(t_2list *lst)
{
	if (!lst)
		return (0);
	return (lst->prev);
}

int	ft_2lstsize(t_2list *lst)
{
	int		i;
	t_2list	*deb;

	deb = lst;
	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
		if (lst == deb)
			return (i);
	}
	return (i);
}
