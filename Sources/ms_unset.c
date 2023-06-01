/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rficht <robin.ficht@free.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 11:03:19 by rficht            #+#    #+#             */
/*   Updated: 2023/06/01 08:55:16 by rficht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_env(char *str, char *env)
{
	while (*str && *env)
	{
		if (*str != *env)
			return (FALSE);
		str++;
		env++;
	}
	if (!(*env))
		return (FALSE);
	if (*env == '=')
		return (TRUE);
	else
		return (FALSE);
}

int	ms_env_pos(char *str, char **envp)
{
	int		n;
	int		j;

	n = 0;
	j = 0;
	while (envp[n])
	{
		if (is_env(str, envp[n]))
			return (n);
		n++;
	}
	return (-1);
}

void	unset_arg(char *arg, t_ms *ms)
{
	int		n;
	int		pos;
	char	**new_envp;

	n = 0;
	pos = ms_env_pos(arg, ms->envp);
	if (pos == -1)
		return ;
	new_envp = calloc((ms_sizeof_tab(ms->envp) - 1), sizeof(char *));
	if (!new_envp)
		ms_crash(ms);
	while (ms->envp[n])
	{
		if (n == pos)
			n++;
		if (ms->envp[n])
			new_envp[n] = ms->envp[n];
		n++;
	}
	ft_freestr(&ms->envp[pos]);
	free(ms->envp);
	ms->envp = new_envp;
}

int	ms_unset(t_cmd *cmd)
{
	int	n;

	if (!cmd->args[0])
	{
		printf("ms_unset received NULL args\n");
		return (1);
	}
	n = 1;
	while (cmd->args[n])
	{
		unset_arg(cmd->args[n], cmd->ms);
		n++;
	}
	return (0);
}
