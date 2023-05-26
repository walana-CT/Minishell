/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rficht <robin.ficht@free.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 19:23:24 by mdjemaa           #+#    #+#             */
/*   Updated: 2023/05/26 16:21:36 by rficht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"

char	**ms_getpath(t_ms *ms)
{
	int		i;

	i = -1;
	while (ms->envp[++i])
		if (ft_strnstr(ms->envp[i], "PATH=", 5))
			return (ft_quotesplit(ms->envp[i] + 5, ':'));
	return (0);
}

int	ms_isbuiltin(char *str)
{
	if (ft_strequal(str, "cd"))
		return (1);
	if (ft_strequal(str, "echo"))
		return (1);
	if (ft_strequal(str, "env"))
		return (1);
	if (ft_strequal(str, "exit"))
		return (1);
	if (ft_strequal(str, "export"))
		return (1);
	if (ft_strequal(str, "pwd"))
		return (1);
	if (ft_strequal(str, "unset"))
		return (1);
	return (0);
}

// /!\ gerer si le nom de commande commence par . ou par /
char	*ms_findpath(char *cmd, char **path)
{
	char	*fullcmd;

	while (path && *path)
	{
		fullcmd = ft_strmanyjoin(*path, "/", cmd, 0);
		if (!access(fullcmd, F_OK | X_OK))
		{
			free(fullcmd);
			return (ft_strdup(*path));
		}
		free(fullcmd);
		path++;
	}
	return (0);
}

int	ms_dealwith_quotes_and_dols(t_cmd *cmd)
{
	int	i;
	int	err;

	err = 0;
	i = -1;
	while (cmd->args[++i])
	{
		if (!ms_dollar_replace(&cmd->args[i], cmd->ms))
			ms_trimquotes(&cmd->args[i]);
		else
			err = 1;
	}
	return (err);
}

int	ms_lex(t_ms *ms)
{
	int		i;
	char	**path;

	i = -1;
	while (++i < ms->nbcmd)
	{
		ms->cmd[i].args = ms_quotesplit(ms->cmd[i].line, ' ', ms);
		if (ms->cmd[i].args)
		{
			ms_dealwith_quotes_and_dols(&ms->cmd[i]);
			ms->cmd[i].cmd_name = ms->cmd[i].args[0];
		}
		else
			return (1);
		path = ms_getpath(ms);
		ms->cmd[i].path = ms_findpath(ms->cmd[i].cmd_name, path);
		ft_freetab(path);
	}
	return (0);
}
