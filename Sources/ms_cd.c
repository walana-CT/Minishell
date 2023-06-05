/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdjemaa <mdjemaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 12:02:02 by rficht            #+#    #+#             */
/*   Updated: 2023/06/05 23:44:28 by mdjemaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	refresh_path(char *path, t_ms *ms)
{
	int		n;
	char	*env_path;
	char	*path_stat;

	n = 0;
	path_stat = "PATH=";
	while (ms->envp[n])
	{
		if (is_env(path_stat, ms->envp[n]))
		{
			env_path = calloc((ft_sstrlen(path) + 6), sizeof(char));
			if (!env_path)
				ms_crash(ms);
			while (*path_stat)
				*env_path++ = *path_stat++;
			while (*path)
				*env_path++ = *path++;
			free(ms->envp[n]);
			ms->envp[n] = env_path;
		}
		n++;
	}
}

int	ms_cd(t_cmd *cmd)
{
	if (!cmd->args[0])
	{
		printf("cd received empty arg\n");
		return (1);
	}
	if (!cmd->args[1])
		return (1);
	if (chdir(cmd->args[1]) == -1)
	{
		ft_putstr_fd("msh: cd: ", 2);
		ft_putstr_fd(cmd->args[1], 2);
		ft_putstr_fd(": Not a directory\n", 2);
		stat_err(1);
		return (1);
	}
	refresh_path(cmd->args[1], cmd->ms);
	return (0);
}
