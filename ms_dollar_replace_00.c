/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_dollar_replace_00.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rficht <robin.ficht@free.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:24:46 by rficht            #+#    #+#             */
/*   Updated: 2023/05/28 15:17:17 by rficht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	env_var_len(char *str)
{
	int	len;

	len = 1;
	while (!ms_is_dol_sep(str[len]))
		len++;
	return (len);
}

int	replace_qm(char **str, int pos, t_ms *ms)
{
	char	*err_str;

	if (ft_strtrunc(str, pos, 2))
		ms_crash(ms);
	err_str = ft_itoa(stat_err(-1));
	if (!err_str)
		ms_crash(ms);
	if (ft_strinsert(str, err_str, pos))
		ms_crash(ms);
	return (0);
}


static int	dol_replace(char **str, int pos, t_ms *ms)
{
	char	*env_val;
	int		var_len;

	//printf("dol replace called \n");
	if ((*str)[pos + 1] == '$')
		return (ft_strtrunc(str, pos, 2));
	if ((*str)[pos + 1] == '?')
		return (replace_qm(str, pos, ms));
	env_val = ms_getenv_val(&str[0][pos + 1], ms);
	//printf("env val found : %s\n", env_val);
	var_len = env_var_len(&str[0][pos]);
	//printf("var len : %d\n", var_len);
	if (ft_strtrunc(str, pos, var_len))
		ms_crash(ms);
	//printf("str after trunc : %s\n", *str);
	if (ft_strinsert(str, env_val, pos))
		return (1);
	//printf("str after strinsert : %s\n", *str);
	return (0);
}

static int	next_dol_pos(char *str)
{
	int	n;

	//printf("next dol pos called on %s\n", str);
	n = 0;
	if (!str)
		return (-1);
	while (str[n])
	{
		if (str[n] == '$' && ms_quote_status(str, n) != 1)
			return (n);
		n++;
	}
	return (-1);
}

int	ms_dollar_replace(char **str, t_ms *ms)
{
	int	dol_pos;

	dol_pos = next_dol_pos(*str);
	while (dol_pos != (-1))
	{
		//printf("dol pos found : %d\n", dol_pos);
		if (dol_replace(str, dol_pos, ms))
			return (1);
		dol_pos = next_dol_pos(*str);
	}
	return (0);
}
