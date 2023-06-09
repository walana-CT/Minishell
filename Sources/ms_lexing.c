/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rficht <robin.ficht@free.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 19:23:24 by mdjemaa           #+#    #+#             */
/*   Updated: 2023/06/09 10:30:08 by rficht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ms_getpath(t_ms *ms)
{
	int		i;

	i = -1;
	while (ms->envp[++i])
		if (ft_strnstr(ms->envp[i], "PATH=", 5))
			return (ms_quotesplit(ms->envp[i] + 5, ':', ms));
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

char	*ms_findpath(char *cmd, char **path)
{
	char	*fullcmd;

	while (path && *path)
	{
		fullcmd = ft_strmanyjoin(*path, "/", cmd, 0);
		if (!access(fullcmd, F_OK | X_OK))
		{
			ft_freestr(&fullcmd);
			return (ft_strdup(*path));
		}
		ft_freestr(&fullcmd);
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

/**
 * will turn lines into an arg array to conform with c program syntax.
 * It will first split with spcaces, replace dollars and remove quotes.
 * @param ms ptr om minishell
 * @return 0 if successful and 1 if fail
 * 
 */
int	ms_lex(t_ms *ms)
{
	int		i;
	char	**path;

	i = -1;
	while (++i < ms->nbcmd)
	{
		ms_trim_empty_dolls(&ms->cmd[i].line, ms);
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
