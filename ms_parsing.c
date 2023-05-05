/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdjemaa <mdjemaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 11:52:15 by mdjemaa           #+#    #+#             */
/*   Updated: 2023/05/05 18:58:44 by mdjemaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"


int	ms_wrongchars(char	*str)
{
	int	i;

	if (ms_str2pipes(str))
		return (ms_error_msg("Syntax error : no || handling in mandatory minishell", TRUE));
	if (str[ft_sstrlen(str) - 1 ] == '|')
		return (ms_error_msg("Syntax error : need command after pipe", TRUE));
	i = -1;
	while (str[++i])
		if (ms_forbiddenchar(str[i]))
			return (ms_error_msg("Syntax error : no '\\' nor ';' handling", TRUE));
	return (FALSE);
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
	if (ms_openquotes(str))
		return(ms_error_msg("Syntax error : quotes not closed", FALSE));
	if (ms_wrongchars(str))
		return(FALSE);
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
		ms->nbcmd = ms_pipesplit(ms);
		if (ms->nbcmd == -1)
			return (FALSE);
	}
	return (TRUE);
}
