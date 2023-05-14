/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_to_strtab.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdjemaa <mdjemaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 10:20:35 by mdjemaa           #+#    #+#             */
/*   Updated: 2023/05/13 19:53:01 by mdjemaa          ###   ########.fr       */
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
	if (!res)
		return (0);
	while (lst)
	{
		res[i++] = ft_strdup(lst->content);
		lst = lst->next;
	}
	res[i] = 0;
	ft_lstclear(&deb, &free);
	return (res);
}
