/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdjemaa <mdjemaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 19:23:24 by mdjemaa           #+#    #+#             */
/*   Updated: 2023/05/12 21:32:59 by mdjemaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"

char	**ms_getpath(t_prog *ms)
{
	int		i;

	i = -1;
	while (ms->envp[++i])
		if (ft_strnstr(ms->envp[i], "PATH=", 5))
			return (ft_quotesplit(ms->envp[i] + 5, ':'));
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
			free(fullcmd);
			return (ft_strdup(*path));
		}
		free(fullcmd);
		path++;
	}
	return (0);
}

int	ms_lex(t_prog *ms)
{
	int		i;
	char	**path;

	i = -1;
	while (++i < ms->nbcmd)
	{
		ms->cmd[i].args = ms_quotesplit(ms->cmd[i].line, ' ');
		if (ms->cmd[i].args)
			ms->cmd[i].cmd_name = ms->cmd[i].args[0];
		path = ms_getpath(ms);
		ms->cmd[i].path = ms_findpath(ms->cmd[i].cmd_name, path);
	}
	ft_freetab(path);
	return (1);
}
