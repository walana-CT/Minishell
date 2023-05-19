/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parsing_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rficht <robin.ficht@free.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 09:12:27 by mdjemaa           #+#    #+#             */
/*   Updated: 2023/05/19 14:28:57 by rficht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"

int	ms_isquote(char c)
{
	if (c == '\'')
		return (1);
	if (c == '\"')
		return (2);
	return (FALSE);
}

// retourne la position de la premiere occurence hors quotes de c dans str
int	ms_where_is(char c, char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == c && !ms_quote_status(str, i))
			return (i);
	return (-1);
}

// renvoie un tableau de int contenant sa size dans [0] puis
// les index de toutes les occurences de c dans str
int	*ms_where_are(char c, char *str)
{
	int	i;
	int	*res;
	int	cpt;

	i = -1;
	cpt = 0;
	while (str[++i])
		if (str[i] == c && !ms_quote_status(str, i))
			cpt++;
	res = malloc(sizeof(int) * (cpt + 1));
	if (!res)
		return (0);
	i = 0;
	res[0] = cpt;
	cpt = -1;
	while (str[++i])
		if (str[i] == c && !ms_quote_status(str, i))
			res[++cpt] = i;
	res[++cpt] = -1;
	return (res);
}

// renvoie 0, 1 ou 2 selon que str[j] est hors quotes, entre
// simples quotes ou entre doubles quotes
/*int	ms_quote_status(char *str, int j)
{
	int	i;
	int	q;

	q = 0;
	i = -1;
	while (++i < j)
	{
		if (q == 0)
			q = ms_isquote(str[i]);
		else if (q == ms_isquote(str[i]))
		{
			if (q == i)
				return (ms_quote_status(str, i));
			q = 0;
		}
	}
	return (q);
}*/

int	ms_quote_status(char *str, int pos)
{
	int	n;
	int	status;

	n = -1;
	status = 0;
	while (++n < pos)
	{
		if (!status)
			status = ms_isquote(str[n]);
		else if (status == ms_isquote(str[n]))
			status = 0;
	}
	if (status == ms_isquote(str[n]))
		status = 0;
	return (status);
}

// retire les quotes et les caracteres entre quotes de str
// et retourne le resultat
char	*ms_noquotes(char *str)
{
	char	*tmp;
	int		i;
	int		j;
	int		cpt;

	i = -1;
	cpt = 0;
	while (++i < (int) ft_sstrlen(str))
		if (ms_quote_status(str, i) == 0)
			cpt++;
	tmp = malloc((1 + cpt) * sizeof(char));
	if (!tmp)
		return (0);
	i = -1;
	j = 0;
	while (++i < (int) ft_sstrlen(str))
	{
		if (ms_quote_status(str, i) == 0)
			tmp[j++] = str[i];
	}
	tmp[j] = 0;
	return (tmp);
}
