/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdjemaa <mdjemaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 11:52:15 by mdjemaa           #+#    #+#             */
/*   Updated: 2023/05/02 18:01:45 by mdjemaa          ###   ########.fr       */
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

int	ms_status(char *str, int j)
{
	int	*status;
	int	i;
	int	q;

	q = 0;
	i = -1;
	while (++i < j)
	{
		if (!q)
			q = ms_isquote(str[i]);
		else
		{
			blabla;
		}
	}
	return (q);
}

void	rline_init(char	*str, t_rline *rl)
{
	rl->line = str;
}

void	ms_parse(char *str, t_rline *rl)
{
	if (ft_strequal(str, "exit"))
		rl->goon = 0;
	else
	{
		rline_init(str, rl);
		ft_printstrtab(rl->line, "tmpCmds");
	}
}
