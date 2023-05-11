/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdjemaa <mdjemaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 10:36:45 by rficht            #+#    #+#             */
/*   Updated: 2023/05/11 12:12:08 by mdjemaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"

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

char	*ms_getenv(char *str, t_prog *prog)
{
	char	**envp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	envp = prog->envp;
	while (envp[i])
	{
		if (envcmp(str, envp[i]))
			return (env_linetovar(envp[i]));
	}
	return (NULL);
}
