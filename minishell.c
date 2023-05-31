/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rficht <robin.ficht@free.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 11:08:22 by mdjemaa           #+#    #+#             */
/*   Updated: 2023/05/31 10:51:34 by rficht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"

int	ms_launch_cmds(t_ms *ms)
{
	if (ms_get_fds(ms))
		return (1);
	if (ms_lex(ms))
		return (1);
	if (ms_exec(ms))
		return (1);
	return (0);
}

/**
 * Represent the main loop of Minishell exec.
 * @param ms address of minishell.
 */
void	minishell(t_ms *ms)
{
	while (1)
	{
		stat_sig(1);
		ms->rl_str = readline("msh > ");
		if (!ms->rl_str)
			ms_exit(NULL);
		stat_sig(0);
		ms->line = ft_strtrim(ms->rl_str, SPACES);
		if (!ms->line)
			ms_crash(ms);
		add_history(ms->line);
		write(ms->histofd, ms->line, ft_sstrlen(ms->line));
		write(ms->histofd, "\n", 1);
		if (ms_get_cmds(ms))
			ms_launch_cmds(ms);
		ms_loop_free(ms);
	}
}

void	ms_gethistory(t_ms *ms)
{
	char	*str;

	str = get_next_line(ms->histofd);
	while (str)
	{
		str[ft_sstrlen(str) - 1] = 0;
		add_history(str);
		free(str);
		str = get_next_line(ms->histofd);
	}		
	free(str);
}

/**
 * Init minishell values to 0.
 * @param ms address of minishell.
 */
int	ms_init(t_ms *ms)
{
	stat_err(0);
	rl_catch_signals = 0;
	ms->pipe = 0;
	ms->nbcmd = 0;
	ms->rl_str = NULL;
	ms->envp = NULL;
	ms->pipe = NULL;
	ms->line = NULL;
	ms->pid = NULL;
	ms->cmd = NULL;
	ms->histofd = open(".ms_history", O_CREAT | O_RDWR, 0644);
	if (ms->histofd == -1)
		ms_crash(ms);
	ms_gethistory(ms);
	return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_ms	ms;

	stat_sig(0);
	ms_init(&ms);
	set_sig();
	copy_env(envp, &ms);
	(void) argv;
	if (argc > 1)
		printf("minishell doesn't need arguments ;)\n");
	minishell(&ms);
	return (0);
}
