/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rficht <robin.ficht@free.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 11:02:48 by rficht            #+#    #+#             */
/*   Updated: 2023/05/15 15:47:37 by rficht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"

int	ms_sizeof_tab(char **my_tab)
{
	int	n;

	if (!my_tab)
		return (-1);
	n = 0;
	while (my_tab[n])
		n++;
	return (n);
}

void	ms_add_envp(char **args, t_ms *ms)
{
	char	**new_envp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_envp = malloc((ms_sizeof_tab(args) + ms_sizeof_tab(ms->envp))
			* sizeof(char *));
	if (!new_envp)
		ms_crash(ms);
	i = 0;
	while (ms->envp[i])
	{
		new_envp[i] = ms->envp[i];
		i++;
	}
	while (args[j])
		new_envp[i++] = args[j++];
	new_envp[i] = NULL;
	free(ms->envp);
	ms->envp = new_envp;
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
	ms_add_envp(cmd->args, cmd->ms);
	return (0);
}
