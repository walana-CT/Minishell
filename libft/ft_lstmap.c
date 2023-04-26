/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdjemaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 15:08:03 by mdjemaa           #+#    #+#             */
/*   Updated: 2022/11/08 18:47:57 by mdjemaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*liste;
	t_list	*elem;
	void	*tmp;

	if (!lst || !f || !del)
		return (NULL);
	liste = NULL;
	while (lst)
	{
		tmp = f(lst->content);
		elem = ft_lstnew(tmp);
		if (!elem)
		{
			free(tmp);
			ft_lstclear(&liste, del);
			return (NULL);
		}
		else
			ft_lstadd_back(&liste, elem);
		lst = lst->next;
	}
	return (liste);
}
