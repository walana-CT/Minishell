/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parsing_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdjemaa <mdjemaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 09:32:57 by mdjemaa           #+#    #+#             */
/*   Updated: 2023/05/29 20:45:31 by mdjemaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"

char	*ms_trim(char c, char *str)
{
	int		i;
	char	*tmp;

	tmp = ft_strdup(str);
	if (!tmp)
		return (0);
	i = ms_where_is(c, tmp);
	while (i != -1)
	{
		ft_strdelchar(&tmp, i);
		i = ms_where_is(c, tmp);
	}
	return (tmp);
}

int	ms_checkpipes(char *str)
{
	int		i;
	char	*tmp;

	tmp = ms_trim(' ', str);
	if (!tmp)
		return (0);
	i = 0;
	while (tmp[i] && tmp[i + 1])
	{
		if (!ms_quote_status(tmp, i)
			&& tmp[i] == '|' && tmp[i + 1] == '|')
			return (free(tmp), 1);
		i++;
	}
	return (free(tmp), 0);
}

int	ms_badchev(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str [i + 1] && str [i + 2])
	{
		if (!ms_quote_status(str, i) && str[i] == '>')
		{
			if (str[i + 1] == '|')
				return (1);
			if (str[i + 1] == '>' && (str[i + 2] == '>' || str[i + 2] == '|'))
				return (1);
		}
		if (!ms_quote_status(str, i) && \
			str[i] == '<' && str[i + 1] == '<' && str[i + 2] == '<')
			return (1);
		if (!ms_quote_status(str, i) && str[i] == '<' && str[i + 1] == '|')
			return (1);
		i++;
	}
	return (0);
}

/**
 * Separates the str line into an str array.
 * @param ms address of minishell.
 * @return size of cmd array.
 */
int	ms_pipesplit(t_ms *ms)
{
	char	**tmp;
	int		i;
	int		size;

	tmp = ms_quotesplit(ms->line, '|', ms);
	if (!tmp)
		ms_crash(ms);
	i = -1;
	size = ms_sizeof_tab(tmp);
	ms->cmd = malloc((size) * sizeof(t_cmd));
	if (!ms->cmd)
		ms_crash(ms);
	while (++i < size)
	{
		ms->cmd[i].line = ft_strtrim(tmp[i], SPACES);
		if (!ms->cmd[i].line)
		{
			ft_freetab(tmp);
			ms_crash(ms);
		}	
	}
	ft_freetab(tmp);
	return (size);
}

/**
 * delete the quotes that are not between quotes.
 * @param str ptr to string.
 * @return 0 or 1 depending on the function worked properly or not.
 */
int	ms_trimquotes(char **str)
{
	int	i;

	i = strlen(*str);
	while (i-- > 0)
	{
		if (((*str)[i] == '\'' || (*str)[i] == '\"')
			&& !ms_quote_status(*str, i))
		{
			if (ft_strdelchar(str, i))
				return (1);
		}
	}
	return (0);
}

/**
 * return TRUE or FALSE depending on whether inapropriate char sequences 
 * are found or not.
 * @param str line of commande after spaces have been trimed.
 */
int	ms_wrongchars(char	*str)
{
	int	i;
	int	last;

	last = ft_sstrlen(str) - 1;
	if (ms_checkpipes(str) || str[0] == '|' || str[last] == '|')
		return (ms_error_msg(SYN_EUNEXT"|", TRUE));
	if (ms_badchev(str) || str[last] == '<' || str[last] == '>')
		return (ms_error_msg(SYN_EUNEXT"< or >", TRUE));
	i = -1;
	while (str[++i])
		if (!ms_quote_status(str, i) && ft_is_in(str[i], FORBID_CHAR) != -1)
			return (ms_error_msg(SYN_EUNEXT FORBID_CHAR, TRUE));
	return (FALSE);
}
