/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdjemaa <mdjemaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 11:08:22 by mdjemaa           #+#    #+#             */
/*   Updated: 2023/05/11 16:07:56 by mdjemaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"

void	ms_printms(t_prog ms)
{
	int	i;

	i = -1;
	printf("Nb commandes %d\n", ms.nbcmd);
	while (++i < ms.nbcmd)
	{
		printf(YELLOW"commande %d\n"RESET, ms.cmd[i].nb);
		printf("Line : %s\n", ms.cmd[i].line);
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
		tmp = readline(GREEN"msh > "RESET);
		add_history(tmp);
		str = ft_strtrim(tmp, SPACES);
		if (str && !ft_strequal(str, ""))
		{
			if (ms_parse(str, ms))
			{
				ms_get_fds(ms);
			}
		}
		ms_printms(*ms);
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
	copy_env(envp, &ms);
	(void) argv;
	if (argc > 1)
		printf("minishell doesn't need arguments ;)\n");
	minishell(&ms);
	//system("leaks minishell");
	return (0);
}
