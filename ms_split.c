/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdjemaa <mdjemaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 17:11:41 by mdjemaa           #+#    #+#             */
/*   Updated: 2023/05/04 17:29:42 by mdjemaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"

void	ms_next_word_quote(char *str, char sep, int *i, int *j)
{
	*i = *j;
	while (str[*i] == sep || ms_status(str, *i))
		(*i)++;
	if (ms_status(str, *i))
	{
		*j = *i + 1;
		while (str[*j] && ms_status(str, *j))
			(*j)++;
	}
	else if (str[*i])
		*j = *i + 1;
	else
		*j = *i;
}

t_list	*ms_quote_init(char *str, char sep, int *i, int *j)
{
	*j = 0;
	ms_next_word_quote(str, sep, i, j);
	return (0);
}

char	**ms_quotesplit(char *s, char sep)
{
	t_list	*l;
	int		i;
	int		j;

	l = ms_quote_init(s, sep, &i, &j);
	while (s[j])
	{
		if (s[i] != sep && (s[j] == sep))
		{
			if (ms_status(s, i))
				ft_lstadd_back(&l, ft_lstnew(ft_substr(s, i + 1, j++ - i - 1)));
			else
				ft_lstadd_back(&l, ft_lstnew(ft_substr(s, i, j - i)));
			ms_next_word_quote(s, sep, &i, &j);
		}
		else
			j++;
	}
	if (j != i && s[j] != sep)
		ft_lstadd_back(&l, ft_lstnew(ft_substr(s, i, j - i)));
	return (ft_lst_to_strtab(l));
}

int	main(void)
{
	char	**split;

	split = ms_quotesplit("Ceci est un test||| de decoupage rigolo ?", ' ');
	ft_printstrtab(split, "-- SPLIT --");
	ft_freetab(split);
	//system("leaks a.out");
	return (0);
}
