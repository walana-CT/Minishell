/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdjemaa <mdjemaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 11:08:22 by mdjemaa           #+#    #+#             */
/*   Updated: 2023/05/15 16:45:13 by mdjemaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"

void	ms_printcmds(t_ms ms)
{
	int	i;

	i = -1;
	printf("Nb commandes %d\n", ms.nbcmd);
	while (++i < ms.nbcmd)
	{
		printf(YELLOW"commande %d\n"RESET, ms.cmd[i].nb);
		ft_printstrtab(ms.cmd[i].args, "ARGS");
		printf("PATH : %s\n", ms.cmd[i].path);
		printf("Filein : %s \t fdin %d\n", ms.cmd[i].filein, ms.cmd[i].fdin);
		printf("Fileout : %s \t fdout %d\n", ms.cmd[i].fileout, ms.cmd[i].fdout);
		printf("Pipein %d \t Pipeout %d\n", ms.pipe[i][0], ms.pipe[i][1]);
	}
}

void	minishell(t_ms *ms)
{
	char	*str;
	char	*tmp;

	while (1)
	{
		tmp = readline(CYAN"msh > "RESET);
		if (!tmp)
			ms_exit(ms);
		str = ft_strtrim(tmp, SPACES);
		add_history(str);
		if (str && !ft_strequal(str, ""))
		{
			if (ms_parse(str, ms))
			{
				ms_get_fds(ms);
				ms_lex(ms);
				ms_exec(ms);
			}
		}
		ms_usual_free(ms, &str, &tmp);
	}
	ms_exit(ms);
}

void	copy_env(char *envp[], t_ms *ms)
{
	char	**envp_copy;
	int		n;

	n = 0;
	envp_copy = calloc(ms_sizeof_tab(envp) + 1, sizeof(char *));
	if (!envp_copy)
		ms_crash(NULL);
	while (envp[n])
	{
		envp_copy[n] = ft_strdup(envp[n]);
		if (!envp_copy[n])
			ms_crash(ms);
		n++;
	}
	ms->envp = envp_copy;
}

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
	copy_env(envp, &ms); // incrementer SHLVL maintenant ?
	(void) argv;
	if (argc > 1)
		printf("minishell doesn't need arguments ;)\n");
	minishell(&ms);
//	system("leaks minishell"); // #SANITIZE en fin de ligne dans la regle .c=.o 
	return (0);
}
