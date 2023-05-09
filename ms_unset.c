/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rficht <robin.ficht@free.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 11:03:19 by rficht            #+#    #+#             */
/*   Updated: 2023/05/05 16:35:40 by rficht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"

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


void	unset_arg(char *arg, t_prog *prog)
{
	int		n;
	int		pos;
	char	**new_envp;

	n = 0;
	pos = env_pos(arg, prog->envp);
	if (pos == -1)
		return ;
	new_envp = malloc((sizeof_tab(prog->envp) - 1) * sizeof(char *));
	if (!new_envp)
		ms_crash(prog);
	while (prog->envp[n])
	{
		if (n == pos)
			n++;
		if (prog->envp[n])
			new_envp[n] = prog->envp[n];
		n++;
	}
	new_envp[n] = NULL;
	free(prog->envp[n]);
	free(prog->envp);
	prog->envp = new_envp;
}

int	ms_unset(t_cmd *cmd)
{
	if (!cmd->args[0])
	{
		printf("ms_unset received NULL args\n");
		return (1);
	}
	cmd->args++;
	while (cmd->args[0])
	{
		unset_arg(cmd->args[0], cmd->prog);
		cmd->args++;
	}
	return (0);
}
