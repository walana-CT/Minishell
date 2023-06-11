/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_dollar_replace_01.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rficht <robin.ficht@free.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 14:44:35 by rficht            #+#    #+#             */
/*   Updated: 2023/06/10 17:25:56 by rficht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_is_dol_sep(char c)
{
	if (c == ' ' || c == 0 || c == '$' || c == '\''
		|| c == '\"' || c == '<' || c == '>')
		return (1);
	else
		return (0);
}

static int	next_empty_dol_pos(char *str, t_ms *ms)
{
	int	n;

	//printf("next dol pos called on %s\n", str);
	n = 0;
	if (!str)
		return (-1);
	while (str[n])
	{
		if (is_doll_replaced(str, n) && !ms_getenv_val(&str[n + 1], ms))
			return (n);
		n++;
	}
	return (-1);
}

int	ms_trim_empty_dolls(char **str, t_ms *ms)
{
	int	empty_dol_pos;

	empty_dol_pos = next_empty_dol_pos(*str, ms);
	while (empty_dol_pos != (-1))
	{
		//printf("dol pos found : %d\n", dol_pos);
		if (dol_replace(str, empty_dol_pos, ms))
			return (1);
		empty_dol_pos = next_empty_dol_pos(*str, ms);
	}
	return (0);
}