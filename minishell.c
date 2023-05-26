/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdjemaa <mdjemaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 11:08:22 by mdjemaa           #+#    #+#             */
/*   Updated: 2023/05/26 22:53:24 by mdjemaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"

int	ms_launch_cmds(t_ms *ms)
{
	if (ms_get_fds(ms))
		return (1);
	if (ms_lex(ms))
		return (1);
	ms_exec(ms);
	return (0);
}

/**
 * Represent the main loop of Minishell exec.
 * @param ms address of minishell.
 */
void	minishell(t_ms *ms)
{
	char	*tmp;

	while (1)
	{
		stat_interactive(1);
		tmp = readline("msh > ");
		stat_interactive(0);
		if (!tmp)
			ms_exit(ms);
		ms->line = ft_strtrim(tmp, SPACES);
		ft_freestr(&tmp);
		if (!ms->line)
			ms_crash(ms);
		add_history(ms->line);
		if (ms->line && !ft_strequal(ms->line, ""))
			if (ms_get_cmds(ms))
				ms_launch_cmds(ms);
		ms_free_ms(ms);
	}
}

/**
 * Init minishell values to 0.
 * @param ms address of minishell.
 */
int	ms_init(t_ms *ms)
{
	rl_catch_signals = 0;
	ms->pipe = 0;
	ms->err = 0;
	ms->nbcmd = 0;
	ms->envp = NULL;
	ms->pipe = NULL;
	ms->line = NULL;
	ms->pid = NULL;
	ms->cmd = NULL;
	return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_ms	ms;

	ms_init(&ms);
	set_sig();
	copy_env(envp, &ms);
	(void) argv;
	if (argc > 1)
		printf("minishell doesn't need arguments ;)\n");
	minishell(&ms);
	return (0);
}
