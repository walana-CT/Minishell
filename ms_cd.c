/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rficht <robin.ficht@free.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 12:02:02 by rficht            #+#    #+#             */
/*   Updated: 2023/05/15 12:14:39 by rficht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"

void	refresh_path(char *path, t_ms *prog)
{
	int		n;
	char	*env_path;
	char	*path_stat;

	n = 0;
	path_stat = "PATH=";
	while (prog->envp[n])
	{
		if (is_env(path_stat, prog->envp[n]))
		{
			env_path = calloc((ft_sstrlen(path) + 6), sizeof(char));
			if (!env_path)
				ms_crash(prog);
			while (*path_stat)
				*env_path++ = *path_stat++;
			while (*path)
				*env_path++ = *path++;
			free(prog->envp[n]);
			prog->envp[n] = env_path;
		}
	}
}

int	ms_cd(t_cmd *cmd)
{
	if (!cmd->args[0])
	{
		printf("cd received empty arg\n");
		return (1);
	}
	cmd->args++;
	if (!cmd->args[0])
	{
		printf("cd needs a path to work\n");
		return (1);
	}
	if (chdir(cmd->args[0]) == -1)
		return (1);
	refresh_path(cmd->args[0], cmd->prog);
	return (0);
}


