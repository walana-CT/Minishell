/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parsing_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdjemaa <mdjemaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 09:32:57 by mdjemaa           #+#    #+#             */
/*   Updated: 2023/05/08 13:39:56 by mdjemaa          ###   ########.fr       */
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

int	ms_str3chev(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str [i + 1] && str [i + 2])
	{
		if (!ms_quote_status(str, i) && \
			str[i] == '>' && str[i + 1] == '>' && str[i + 2] == '>')
			return (TRUE);
		if (!ms_quote_status(str, i) && \
			str[i] == '<' && str[i + 1] == '<' && str[i + 2] == '<')
			return (TRUE);
		i++;
	}
	return (FALSE);
}

// liste de caracteres interdits
int	ms_forbiddenchar(char c)
{
	if (c == '\\' || c == ';')
		return (TRUE);
	return (FALSE);
}

int	ms_pipesplit(t_prog *ms)
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

void	ms_printcmds(t_prog ms)
{
	int	i;

	i = -1;
	printf("%d commandes\n", ms.nbcmd);
	while (++i < ms.nbcmd)
		printf("%s\n", ms.cmd[i].line);
}