/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parsing_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rficht <robin.ficht@free.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 09:32:57 by mdjemaa           #+#    #+#             */
/*   Updated: 2023/05/26 16:38:27 by rficht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"

int	ms_str2pipes(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str [i + 1])
	{
		if (!ms_quote_status(str, i)
			&& str[i] == '|' && str[i + 1] == '|')
			return (TRUE);
		i++;
	}
	return (FALSE);
}

int	ms_badchev(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str [i + 1] && str [i + 2])
	{
		if (!ms_quote_status(str, i) && \
			str[i] == '>' && str[i + 1] == '>' && \
			(str[i + 2] == '>' || str[i + 2] == '|'))
			return (TRUE);
		if (!ms_quote_status(str, i) && \
			str[i] == '<' && str[i + 1] == '<' && str[i + 2] == '<')
			return (TRUE);
		i++;
	}
	return (FALSE);
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
