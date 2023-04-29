/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rficht <robin.ficht@free.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 18:18:03 by mdjemaa           #+#    #+#             */
/*   Updated: 2023/04/29 17:36:14 by rficht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Includes/pipex_bonus.h"

char	**px_get_path(char **envp)
{
	int		i;

	i = -1;
	while (envp[++i])
		if (ft_strnstr(envp[i], "PATH=", 5))
			return (ft_quotesplit(envp[i] + 5, ':'));
	return (0);
}

char	*px_prefix_cmd(char *cmd, char **path)
{
	char	*fullcmd;

	while (path && *path)
	{
		fullcmd = ft_strmanyjoin(*path, "/", cmd, 0);
		if (!access(fullcmd, F_OK | X_OK))
			return (fullcmd);
		free(fullcmd);
		path++;
	}
	fullcmd = ft_strdup(cmd);
	return (fullcmd);
}

int	px_file_err(char *file)
{
	write(2, "pipex: ", 7);
	write(2, file, ft_sstrlen(file));
	write(2, ": No such file or directory\n", 28);
	return (127);
}

void	px_bad_child_ending(char *str)
{
	char	*error;

	error = ft_strmanyjoin("pipex: ", str, ": command not found\n", 0);
	write(2, error, ft_strlen(error));
	free(error);
	exit(127);
}
