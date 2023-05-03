/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdjemaa <mdjemaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 11:52:15 by mdjemaa           #+#    #+#             */
/*   Updated: 2023/05/03 17:08:38 by mdjemaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"

int	ms_isquote(char c)
{
	if (c == '\'')
		return (1);
	if (c == '\"')
		return (2);
	return (0);
}

// renvoie 0, 1 ou 2 selon que str[j] est hors quotes, entre simples quotes ou entre doubles quotes
int	ms_status(char *str, int j)
{
	int	i;
	int	q;

	q = 0;
	i = -1;
	while (++i <= j)
	{
		if (q == 0)
			q = ms_isquote(str[i]);
		else if (q == ms_isquote(str[i]))
		{
			if (i == j)
				return (q);
			q = 0;
		}
	}
	return (q);
}

// retire les quotes et les caracteres entre quotes de str et retourne le resultat
char	*ms_noquotes(char *str)
{
	char	*tmp;
	int		i;
	int		j;
	int		cpt;

	i = -1;
	cpt = 0;
	while (++i < (int) ft_sstrlen(str))
	{
		if (ms_status(str, i) == 0)
			cpt++;	
	}
	tmp = malloc((1 + cpt) * sizeof(char));
	if (!tmp)
		return (0);
	i = -1;
	j = 0;
	while (++i < (int) ft_sstrlen(str))
	{
		if (ms_status(str, i) == 0)
			tmp[j++] = str[i];
	}
	tmp[j] = 0;
	return (tmp);
}

// liste de caracteres interdits pares un pipe
int	ms_forbiddenchar(char c)
{
	if (c == '|')
		return (1);
	return (0);
}

int	ms_wrongchars(char	*str)
{
	int	i;

	i = ft_where_is('\\', str);
	if (i != -1 && !ms_status(str, i))
		return (1);
	i = ft_where_is('|', str);
	if (i != -1)
		if (str[i + 1] && ms_forbiddenchar(str[i + 1]))
			return (1);
	return (0);
}

int	ms_openquotes(char *str)
{
	int 	open;
	int		i;
	char	quote;

	i = -1;
	open = 0;
	while (str[++i])
	{
		if (!open && ms_isquote(str[i]))
		{
			quote = str[i];
			open = 1;
		}
		else if (str[i] == quote)
			open = 0;
	}
	return (open);
}

// 0 si caracteres interdits, quotes ouverts, autres pbs de syntaxe
int	ms_syntax_ok(char *str)
{
	char	*tmp;

	if (ms_openquotes(str))
		return(printf(RED"Open quotes !\n"RESET));
	tmp = ms_noquotes(str);
	if (!tmp)
		return (0);
	if (ms_wrongchars(tmp))
		return(printf(RED"Forbidden char !\n"RESET));
	return (1);
}

int	ms_parse(char *str, t_prog *ms)
{
	if (ft_strequal(str, "exit"))
		ms->goon = 0;
	else
	{
		ms->line = str;
		printf("%s\n", ms->line);
		ms_syntax_ok(ms->line);
	}
	return (1);
}
