/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rficht <robin.ficht@free.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 11:02:48 by rficht            #+#    #+#             */
/*   Updated: 2023/05/05 09:19:40 by rficht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"

int	sizeof_tab(char **my_tab)
{
	int n;

	if (!my_tab)
		return(-1);
	n = 0;
	while (my_tab[n])
		n++;
	return (n);
}


void	ms_add_env(char **args, t_prog *prog)
{
	char **new_envp;
	int i;
	int j;

	i = 0;
	j = 0;

	new_envp = malloc((sizeof_tab(args) + sizeof_tab(prog->envp)) * sizeof(char *));
	if (!new_envp)
		ms_crash(prog);
	i = 0;
	while (prog->envp[i])
	{
		new_envp[i] = prog->envp[i];
		i++;
	}
	while (args[j])
		new_envp[i++] = args[j++];
	new_envp[i] = NULL;
	free(prog->envp);
	prog->envp = new_envp;	
}



int	ms_export(t_cmd *cmd)
{
	if (!cmd->args[0])
	{
		printf("export received empty arg\n");
		return (1);
	}
	cmd->args++;
	if (!cmd->args[0])
	{
		ms_env(cmd);
		return (0);
	}
	ms_add_envp(cmd->args, cmd->prog);
}
