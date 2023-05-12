/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdjemaa <mdjemaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 11:08:22 by mdjemaa           #+#    #+#             */
/*   Updated: 2023/05/12 21:33:01 by mdjemaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"

void	ms_print_fdstatus(t_prog ms)
{
	int	i;

	i = -1;
	if (ms.pipe || ms.nbcmd)
		puts("__________________________________________________\n");
	while (ms.pipe && ms.pipe[++i])
		printf("pipe[%d][0] : %d, pipe[%d][1] : %d\n", i, ms.pipe[i][0], i, ms.pipe[i][1]);
	i = -1;
	while (++i < ms.nbcmd)
		printf("cmd %d fdin : %d, fdout : %d\n", i, ms.cmd[i].fdin, ms.cmd[i].fdout);
	if (ms.pipe || ms.nbcmd)
		puts("__________________________________________________");
}

void	ms_printcmds(t_prog ms)
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

void	minishell(t_prog *ms)
{
	char	*str;
	char	*tmp;

	while (ms->goon)
	{
		ms_print_fdstatus(*ms);
		tmp = readline(CYAN"msh > ");
		printf(RESET);
		str = ft_strtrim(tmp, SPACES);
		add_history(str);
		if (str && !ft_strequal(str, ""))
		{
			if (ms_parse(str, ms))
			{
				ms_get_fds(ms);
				ms_lex(ms);
			}
		}
		ms_printcmds(*ms);
		ms_usual_free(ms, str, tmp);
	}
	printf("exit\n");
}

void	copy_env(char *envp[], t_prog *prog)
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
			ms_crash(prog);
		n++;
	}
	prog->envp = envp_copy;
}

int	main(int argc, char *argv[], char *envp[])
{
	t_prog	ms;

	set_sig();
	copy_env(envp, &ms); // incrementer SHLVL maintenant ?
	if (terminal_init(&ms))
		ms_crash(NULL);
//	copy_env(envp, &ms); // normal deux fois (voir ligne 95) ? ca fait leaker
	(void) argv;
	if (argc > 1)
		printf("minishell doesn't need arguments ;)\n");
	minishell(&ms);
	system("leaks minishell"); // #SANITIZE en fin de ligne dans la regle .c=.o 
	return (0);
}
