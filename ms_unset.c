/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rficht <robin.ficht@free.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 11:03:19 by rficht            #+#    #+#             */
/*   Updated: 2023/05/05 09:20:58 by rficht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"

int	is_env(char *str, char *env)
{
	while (*str && *env)
	{
		if (*str != *env)
			return(FALSE);
		str++;
		env++;		
	}
	if (!(*env))
		return(FALSE);
	if (*env == '=')
		return(TRUE);
	else
		return (FALSE);	
}

void	unset_arg(char *arg, t_prog *prog)
{
	int i;
	int j;
	char **new_envp;

	i = 0;
	j = 0;
	while (prog->envp[i])
	{
		if (is_env(arg, prog->envp[i]))
		{
			free(prog->envp[i]);
			new_envp = malloc((sizeof_tab(prog->envp) - 1) * sizeof(char *));
			if (!new_envp)
				ms_crash(prog);
			while (prog->envp[j])
			{
				if (j == i)
					j++;
				if (prog->envp[j])
					new_envp[j] = prog->envp[j];				
				j++;
			}
		}
	}
}

void	ms_unset(t_cmd *cmd)
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
}
