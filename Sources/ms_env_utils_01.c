/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env_utils_01.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdjemaa <mdjemaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 09:25:44 by rficht            #+#    #+#             */
/*   Updated: 2023/06/12 11:08:46 by mdjemaa          ###   ########.fr       */
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

/**
 * Create a copy of envp directclty inside minishell so we can modify it later.
 * Also increase the shlvl. 
 * @param envp The original envp
 * @param ms The addresse of minishell
 */
void	copy_env(char *envp[], t_ms *ms)
{
	char	**envp_copy;
	int		n;

	n = 0;
	envp_copy = calloc(ms_sizeof_tab(envp) + 1, sizeof(char *));
	if (!envp_copy)
		ms_crash(NULL);
	while (envp[n])
	{
		envp_copy[n] = ft_strdup(envp[n]);
		if (!envp_copy[n])
			ms_crash(ms);
		n++;
	}
	ms->envp = envp_copy;
	if (incr_shell_lvl(ms))
		ms_crash(ms);
	ms_exportvar("OLDPWD", ms);
}
