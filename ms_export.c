/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rficht <robin.ficht@free.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 11:02:48 by rficht            #+#    #+#             */
/*   Updated: 2023/05/28 15:09:58 by rficht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"

void	sort_tab(char **str_tab)
{
	int		is_finished;
	char	*tmp;
	int		n;

	is_finished = 0;
	while (!is_finished)
	{
		is_finished = 1;
		n = 0;
		while (str_tab[n] && str_tab[n + 1])
		{
			if (ft_strcmp(str_tab[n], str_tab [n + 1]) > 0)
			{
				tmp = str_tab[n];
				str_tab[n] = str_tab[n + 1];
				str_tab[n + 1] = tmp;
				is_finished = 0;
			}
			n++;
		}
	}
}

void	ms_no_arg_export(t_ms *ms, int fd_out)
{
	char	**envp_copy;
	int		n;

	envp_copy = calloc(ms_sizeof_tab(ms->envp) + 1, sizeof(char *));
	if (!envp_copy)
	{
		printf("ms_no_arg_export failed to malloc\n");
		return ;
	}
	n = -1;
	while (ms->envp[++n])
		envp_copy[n] = ms->envp[n];
	sort_tab(envp_copy);
	ms_printtab(envp_copy, fd_out);
	free(envp_copy);
	envp_copy = NULL;
}

void	env_addvar(char *new_var, t_ms *ms)
{
	char	**new_envp;
	int		n;

	n = -1;
	new_envp = calloc(ms_sizeof_tab(ms->envp) + 2, sizeof(char *));
	if (!new_envp)
		ms_crash(ms);
	while (ms->envp[++n])
		new_envp[n] = ms->envp[n];
	new_envp[n] = strdup(new_var);
	free(ms->envp);
	ms->envp = new_envp;
}

void	ms_exportvar(char *new_var, t_ms *ms)
{
	int	env_varl;


	env_varl = ms_getenv_varl(new_var, ms);
	if (env_varl >= 0)
	{
		free(ms->envp[env_varl]);
		ms->envp[env_varl] = ft_strdup(new_var);
	}
	else
		env_addvar(new_var, ms);
}

int	ms_export(t_cmd *cmd)
{
	int		n;

	n = 0;
	if (!cmd->args[0])
	{
		printf("export received empty arg\n");
		return (1);
	}
	if (!cmd->args[1])
	{
		ms_no_arg_export(cmd->ms, cmd->fdout);
		return (0);
	}
	while (cmd->args[++n])
		ms_exportvar(cmd->args[n], cmd->ms);
	return (0);
}
