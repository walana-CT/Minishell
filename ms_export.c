/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rficht <robin.ficht@free.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 11:02:48 by rficht            #+#    #+#             */
/*   Updated: 2023/05/17 11:23:18 by rficht           ###   ########.fr       */
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
	if (!cmd->args[1])
	{
		ms_no_arg_export(cmd->ms, cmd->fdout);
		return (0);
	}
	ms_add_envp(cmd->args, cmd->ms);
	return (0);
}
