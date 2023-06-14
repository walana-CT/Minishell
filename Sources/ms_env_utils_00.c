/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env_utils_00.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rficht <robin.ficht@free.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 10:36:45 by rficht            #+#    #+#             */
/*   Updated: 2023/06/14 11:46:05 by rficht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	incr_shell_lvl(t_ms *ms)
{
	char	*shlvl_val;
	long	new_val;
	char	*new_valstr;

	shlvl_val = ms_getenv_val("SHLVL", ms);
	if (shlvl_val == NULL)
		ms_exportvar("SHLVL=1", ms);
	else
	{
		new_val = ft_atoi(shlvl_val);
		new_val++;
		new_valstr = ft_itoa(new_val);
		ms_exportvar(ft_strjoin("SHLVL=", new_valstr), ms);
		ft_freestr(&new_valstr);
	}
	return (0);
}

char	*env_linetovar(char *envl)
{
	while (*envl != '=' && *envl)
		envl++;
	if (*envl == 0)
		return (NULL);
	envl++;
	return (envl);
}

int	envcmp(char *str, char *envl)
{
	int	n;

	n = 0;
	while (!ms_is_dol_sep(str[n]) && envl[n])
	{
		if (envl[n] != str[n])
			return (FALSE);
		if (envl[n] == '=' && str[n] == '=')
			return (TRUE);
		n++;
	}
	if ((ms_is_dol_sep(str[n]) || str[n] == '=')
		&& (envl[n] == 0 || envl[n] == '='))
		return (TRUE);
	else
		return (FALSE);
}

/**
 * search if a variable exists and return a ptr to it's value start
 * @param envp the variable we are looking for
 * @param ms the addresse of minishell
 * @return a pointer to the first 
 */
char	*ms_getenv_val(char *str, t_ms *ms)
{
	char	**envp;
	int		i;

	i = -1;
	envp = ms->envp;
	while (envp[++i])
	{
		if (envcmp(str, envp[i]))
			return (env_linetovar(envp[i]));
	}
	return (NULL);
}

/**
 * Search if a variable exists and return a ptr to it if it does
 * @param envp the variable we are looking for
 * @param ms the addresse of minishell
 * @return a pointer to the first 
 */
int	ms_getenv_varl(char *str, t_ms *ms)
{
	char	**envp;
	int		i;

	i = -1;
	envp = ms->envp;
	while (envp[++i])
	{
		if (envcmp(str, envp[i]))
			return (i);
	}
	return (-1);
}
