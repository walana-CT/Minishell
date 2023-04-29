/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_to_strtab.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rficht <robin.ficht@free.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 10:20:35 by mdjemaa           #+#    #+#             */
/*   Updated: 2023/04/29 15:25:27 by rficht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/libft.h"

char	**ft_lst_to_strtab(t_list *lst)
{
	char	**res;
	int		i;
	t_list	*deb;

	deb = lst;
	i = 0;
	res = malloc((1 + ft_lstsize(lst)) * sizeof(char *));
	while (lst)
	{
		res[i++] = ft_strdup(lst->content);
		lst = lst->next;
	}
	res[i] = 0;
	ft_lstclear(&deb, &free);
	return (res);
}
