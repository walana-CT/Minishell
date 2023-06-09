/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rficht <robin.ficht@free.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 12:02:02 by rficht            #+#    #+#             */
/*   Updated: 2023/06/08 17:48:39 by rficht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	refresh_old(t_ms *ms)
{
	char	buffer[MAXPATHLEN + 1];
	char	*val_path;
	char	*path;

	buffer[MAXPATHLEN] = 0;
	val_path = ms_getenv_val("PWD", ms);
	path = ft_strjoin("OLDPWD=", val_path);
	//printf("refresh_old path try to refresh : %s\n", path);
	ms_exportvar(path, ms);
}

void	refresh_pwd(t_ms *ms)
{
	char	buffer[MAXPATHLEN + 1];
	char	*val_path;
	char	*path;

	buffer[MAXPATHLEN] = 0;
	val_path = getcwd(buffer, MAXPATHLEN);
	path = ft_strjoin("PWD=", val_path);
	//printf("refresh path try to refresh : %s\n", path);
	ms_exportvar(path, ms);
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
		ft_putstr_fd(": No such file or directory\n", 2);
		stat_err(1);
		return (1);
	}
	refresh_old(cmd->ms);
	refresh_pwd(cmd->ms);
	return (0);
}
