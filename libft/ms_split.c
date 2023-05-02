/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdjemaa <mdjemaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 19:29:41 by mdjemaa           #+#    #+#             */
/*   Updated: 2023/04/30 19:21:10 by mdjemaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/libft.h"

struct s_split
{
	char	*strbase;
	int		squote;
	int		dquote;
	int		i;
	int		j;
	char	sep;
	t_2list	*split;
} t_split;
 
int	ms_quote(char c, char *quote)
{
	if (c == '\'' || c == '\"')
	{
		*quote = c;
		return (1);
	}
	quote = 0;
	return (0);
}

int	ms_goto_nextquote(char *str, char q, int *j)
{
	int	i;

	i = *j;
	while (str[i] && str[i] != q)
		i++;
	*j = i;
	if (str[i])
		return (1);
	return (0);
}

// decoupe str selon sep, ignore sep s'il est placé entre " ou '
char	**ms_split(char *str, char sep)
{
	t_split	*s;

	ms_splitinit(s, str, sep);
	while (str[s->i])
	{
		if (ms_quote(s))
			ms_goto_nextquote(str, q, &i);
		if (str[i])
			write(1, &str[i], 1);
		i++;
	}
	return (0);
}

int	main(void)
{
	ms_split("salut c'est moi !", ' ');
	return (0);
}