/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rficht <robin.ficht@free.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 10:36:45 by rficht            #+#    #+#             */
/*   Updated: 2023/05/15 15:17:44 by rficht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	while (str[n] != ' ' && str[n])
	{
		if (envl[n] == '=')
			return (FALSE);
		if (envl[n] != str [n])
			return (FALSE);
		n++;
	}
	if (envl[n] == '=')
		return (TRUE);
	else
		return (FALSE);
}

char	*ms_getenv(char *str, t_ms *ms)
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
