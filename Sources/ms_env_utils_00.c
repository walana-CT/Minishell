/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env_utils_00.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rficht <robin.ficht@free.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 10:36:45 by rficht            #+#    #+#             */
/*   Updated: 2023/06/01 09:25:05 by rficht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	incr_shell_lvl(t_ms *ms)
{
	char	*shlvl_envl;
	int		n;

	shlvl_envl = ms_getenv_val("SHLVL", ms);
	n = 0;
	while (shlvl_envl[n])
		n++;
	if (shlvl_envl[n - 1] == '9')
	{
		if (ft_strresize(&shlvl_envl, 1))
			return (1);
		while (shlvl_envl[--n] == '9')
			shlvl_envl[n] = '0';
	}
	else
		n--;
	shlvl_envl[n] += 1;
	return (0);
}

char	*env_linetovar(char *envl)
{
	//printf("envl line to var called on %s\n", envl);
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
	//printf("comparing %s with %s\n", str, envl);
	while (!ms_is_dol_sep(str[n]) && envl[n])
	{
		//printf("comparing %c with %c\n", str[n], envl[n]);
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
	//printf("searshing for %s inside env\n", str);
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
	//printf("searshing for %s inside env\n", str);
	while (envp[++i])
	{
		if (envcmp(str, envp[i]))
			return (i);
	}
	return (-1);
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
}
