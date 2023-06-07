/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env_utils_01.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rficht <robin.ficht@free.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 09:25:44 by rficht            #+#    #+#             */
/*   Updated: 2023/06/07 11:11:51 by rficht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_env_var_len(char *str)
{
	int	len;

	len = 1;
	while (!ms_is_dol_sep(str[len]))
		len++;
	return (len);
}

int	ms_env_hasval(char *str)
{
	while (*str)
	{
		if (*str == '=')
			return (TRUE);
		str++;
	}
	return (FALSE);
}
