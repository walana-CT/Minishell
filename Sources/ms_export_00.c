/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export_00.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rficht <robin.ficht@free.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 11:02:48 by rficht            #+#    #+#             */
/*   Updated: 2023/06/07 11:30:44 by rficht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



void	env_addvar(char *new_var, t_ms *ms)
{
	char	**new_envp;
	int		n;

	n = -1;
	new_envp = calloc(ms_sizeof_tab(ms->envp) + 2, sizeof(char *));
	if (!new_envp)
		ms_crash(ms);
	while (ms->envp[++n])
		new_envp[n] = ms->envp[n];
	new_envp[n] = strdup(new_var);
	free(ms->envp);
	ms->envp = new_envp;
}

int	valid_var(char *new_var)
{
	if (*new_var == '=')
		return (FALSE);
	while (*new_var && *new_var != '=')
	{
		if (*new_var == '-')
			return (FALSE);
		if (ft_isdigit(*new_var))
			return (FALSE);
		new_var++;
	}
	return (TRUE);
}

int	ms_exportvar(char *new_var, t_ms *ms)
{
	int	env_varl;

	if (!valid_var(new_var))
	{
		ft_putstr_fd(" not a valid identifier\n", 2);
		return (1);
	}
	env_varl = ms_getenv_varl(new_var, ms);
	if (env_varl >= 0)
	{
		free(ms->envp[env_varl]);
		ms->envp[env_varl] = ft_strdup(new_var);
	}
	else
		env_addvar(new_var, ms);
	return (0);
}

int	ms_export(t_cmd *cmd)
{
	int		n;

	n = 0;
	if (!cmd->args[0])
	{
		printf("export received empty arg\n");
		return (1);
	}
	if (!cmd->args[1])
	{
		ms_no_arg_export(cmd->ms, cmd->fdout);
		return (0);
	}
	while (cmd->args[++n])
		if (ms_exportvar(cmd->args[n], cmd->ms))
			return (1);
	return (0);
}
