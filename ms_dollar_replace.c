/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_dollar_replace.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rficht <robin.ficht@free.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:24:46 by rficht            #+#    #+#             */
/*   Updated: 2023/05/12 10:08:03 by rficht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"

static int	is_dol_sep(char c)
{
	if (c == ' ' || c == 0 || c == '$' || c == '\''
		|| c == '"' || c == '<' || c == '>')
		return (1);
	else
		return (0);
}

static int	env_var_len(char *str)
{
	int	len;

	len = 1;
	while (!is_dol_sep(str[len]))
		len++;
	return (len);
}

static int	dol_replace(char **str, int pos, t_prog *prog)
{
	char	*env_val;
	int		var_len;

	env_val = ms_getenv(&str[0][pos + 1], prog);
	var_len = env_var_len(&str[0][pos]);
	if (ft_strtrunc(str, pos, var_len))
		return (1);
	if (ft_strinsert(str, env_val, pos))
		return (1);
	return (0);
}

static int	next_dol_pos(char *str)
{
	int	n;

	n = 0;
	while (str[n])
	{
		if (str[n] == '$' && ms_quote_status(str, n) != 1)
		{
			if (n == 0)
				return (n);
			else if (str[n - 1] == ' ')
				return (n);
		}
		n++;
	}
	return (-1);
}

int	dollar_replace(char **str, t_prog *prog)
{
	int	dol_pos;

	dol_pos = next_dol_pos(*str);
	while (dol_pos != -1)
	{
		if (dol_replace(str, dol_pos, prog))
			return (1);
		dol_pos = next_dol_pos(*str);
	}
	return (0);
}
