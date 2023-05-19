/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parsing_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rficht <robin.ficht@free.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 09:32:57 by mdjemaa           #+#    #+#             */
/*   Updated: 2023/05/19 14:36:33 by rficht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"

int	ms_str2pipes(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str [i + 1])
	{
		if (!ms_quote_status(str, i) && \
			str[i] == '|' && str[i + 1] == '|')
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

int	ms_pipesplit(t_ms *ms)
{
	char	**tmp;
	int		i;
	int		size;

	tmp = ms_quotesplit(ms->line, '|');
	if (!tmp)
		return (-1);
	i = -1;
	size = ms_sizeof_tab(tmp);
	ms->cmd = malloc((size) * sizeof(t_cmd));
	if (!ms->cmd)
		return (-1);
	while (++i < size)
		ms->cmd[i].line = ft_strtrim(tmp[i], SPACES);
	ft_freetab(tmp);
	return (size);
}

int	ms_trimquotes(char **str)
{
	int	i;

	/*printf("trimquotes called on %s\n", str);
	i = 0;
	while (str[i])
	{
		printf("%c : %d\n", str[i], ms_quote_status(str, i));
		i++;
	}*/
	i = strlen(*str);
	while (i-- > 0)
	{
		//printf("testing char %c : status %d\n", str[i], ms_quote_status(*str, i));
		if (((*str)[i] == '\'' || (*str)[i] == '\"')
			&& !ms_quote_status(*str, i))
		{
			if (ft_strdelchar(str, i))
				return (1);
			//printf("str after delchar %s : \n", str);
		}
	}
	return (0);
}
