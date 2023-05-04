/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdjemaa <mdjemaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 11:52:15 by mdjemaa           #+#    #+#             */
/*   Updated: 2023/05/04 12:11:36 by mdjemaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"


int	ms_wrongchars(char	*str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (ms_forbiddenchar(str[i]))
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
//	char	*tmp;

	if (ms_openquotes(str))
		return(printf(RED"Open quotes\n"RESET));
/*	tmp = ms_noquotes(str);
	if (!tmp)
		return (0);
	if (ms_wrongchars(tmp))
*/	if (ms_wrongchars(str))
		return(printf(RED"Forbidden char\n"RESET));
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
