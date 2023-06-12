/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export_00.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rficht <robin.ficht@free.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 11:02:48 by rficht            #+#    #+#             */
/*   Updated: 2023/06/12 11:52:39 by rficht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_addvar(char *new_var, t_ms *ms)
{
	char	**new_envp;
	int		n;

	printf("envreplace called\n");
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
	if (*new_var == '=' || *new_var == '+')
		return (FALSE);
	while (*new_var && *new_var != '=')
	{
		if (*new_var == '-')
			return (FALSE);
		else if (*new_var == '+')
		{
			if (*(new_var + 1) == '=')
				return (TRUE);
			else
				return (FALSE);
		}
		else if (!ft_isalnum(*new_var) && *new_var != '_')
			return (FALSE);
		new_var++;
	}
	return (TRUE);
}



/**
 * test wether its an export += or not
 * @param new_var the new variable to export.
 * @return boolean.
 */
int	is_envinsert(char *new_var)
{
	int	n;

	n = 0;
	while (new_var[n])
	{
		printf("testing	%c\n", new_var[n]);
		if (new_var[n] == '+')
			return (TRUE);
		if (new_var[n] == '=')
			return (FALSE);
		n++;
	}
	return (FALSE);
}

int	envinsert(t_ms *ms, char *new_var, int env_varl)
{
	int	n;

	printf("envinsert called\n");
	n = 0;
	while (ms->envp[env_varl][n])
		n++;
	if (ft_strinsert(ms->envp + env_varl, new_var, n))
		return (1);
	return (0);
}


/**
 * export a new var into ms_env. Carefull, it doesn't free new var.
 * @param new_var the new variable to export.
 * @param ms a pointer to minishell.
 * @return 0 if succes 1 if fail. 
 */
int	ms_exportvar(char *new_var, t_ms *ms)
{
	int	env_varl;

	if (!valid_var(new_var))
	{
		ft_putstr_fd(" not a valid identifier\n", 2);
		return (1);
	}
	env_varl = ms_getenv_varl(new_var, ms);
	if (env_varl == -1)
		env_addvar(new_var, ms);
	else
	{
		if (is_envinsert(new_var))
			envinsert(ms, new_var, env_varl);
		else
		{
			printf("envreplace called\n");			
			free(ms->envp[env_varl]);
			ms->envp[env_varl] = ft_strdup(new_var);
		}		
	}
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
