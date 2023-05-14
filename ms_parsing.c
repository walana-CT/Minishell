/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdjemaa <mdjemaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 11:20:11 by mdjemaa           #+#    #+#             */
/*   Updated: 2023/05/12 13:18:13 by mdjemaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"

int	ms_wrongchars(char	*str)
{
	int	i;
	int	last;

	last = ft_sstrlen(str) - 1;
	if (ms_str2pipes(str) || str[0] == '|' || str[last] == '|')
		return (ms_error_msg(SYN_EUNEXT"|", TRUE));
	if (ms_badchev(str) || str[last] == '<' || str[last] == '>')
		return (ms_error_msg(SYN_EUNEXT"< or >", TRUE));
	i = -1;
	while (str[++i])
		if (!ms_quote_status(str, i) && ft_is_in(str[i], FORBID_CHAR) != -1)
			return (ms_error_msg(SYN_EUNEXT FORBID_CHAR, TRUE));
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
	// if (!ms_redir_checker(str)) // doit trim apres < ou >, check FORBID, etc ?
	// 	return (FALSE);
	return (TRUE);
}

int	ms_cmds_init(t_prog *ms)
{
	int	i;

	i = -1;
	ms->nbcmd = ms_pipesplit(ms);
	if (ms->nbcmd == -1)
		return (FALSE);
	ms->pipe = malloc((1 + ms->nbcmd) * sizeof(int *));
	while (++i < ms->nbcmd)
	{
		ms->pipe[i] = malloc(2 * sizeof(int));
		if (!ms->pipe[i] || pipe(ms->pipe[i]) == -1)
			return (FALSE);
		ms->cmd[i].nb = i;
		ms->cmd[i].args = 0;
		ms->cmd[i].cmd_name = 0;
		ms->cmd[i].fdin = 0;
		ms->cmd[i].filein = 0;
		ms->cmd[i].fileout = 0;
		ms->cmd[i].fdout = 1;
		ms->cmd[i].limiter = 0;
		ms->cmd[i].path = 0;
		ms->cmd[i].prog = ms;
	}
	ms->pipe[i] = 0;
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
		if (!ms_cmds_init(ms))
			return (FALSE);
	}
	return (TRUE);
}
