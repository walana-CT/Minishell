/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdjemaa <mdjemaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 11:52:15 by mdjemaa           #+#    #+#             */
/*   Updated: 2023/05/08 15:19:29 by mdjemaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"

int	ms_wrongchars(char	*str)
{
	int	i;
	int	last;

	last = ft_sstrlen(str) - 1;
	if (ms_str2pipes(str))
		return (ms_error_msg("Syntax error : found ||", TRUE));
	if (ms_str3chev(str))
		return (ms_error_msg("Syntax error : found <<< or >>>", TRUE));
	if (str[0] == '|' || str[last] == '|')
		return (ms_error_msg("Syntax error : pipe : unexpected token", TRUE));
	if (str[last] == '<' || str[last] == '>')
		return (ms_error_msg("Syntax error : unexpected token", TRUE));
	i = -1;
	while (str[++i])
		if (!ms_quote_status(str, i) && ms_forbiddenchar(str[i]))
			return (ms_error_msg("Syntax error : found \\ or ;", TRUE));
	return (FALSE);
}

int	ms_openquotes(char *str)
{
	int		open;
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
	if (ms_openquotes(str))
		return (ms_error_msg("Syntax error : quotes not closed", FALSE));
	if (ms_wrongchars(str))
		return (FALSE);
	return (TRUE);
}

int	ms_parse(char *str, t_prog *ms)
{
	if (ft_strequal(str, "exit"))
	{
		ms->goon = 0;
		ms->nbcmd = 0;
		return (FALSE);
	}
	else
	{
		ms->line = str;
		if (!ms_syntax_ok(ms->line))
			return (FALSE);
		// trim ici avec # ?
		ms->nbcmd = ms_pipesplit(ms);
		if (ms->nbcmd == -1)
			return (FALSE);
	}
	return (TRUE);
}
