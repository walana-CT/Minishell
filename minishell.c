/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rficht <robin.ficht@free.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 11:08:22 by mdjemaa           #+#    #+#             */
/*   Updated: 2023/05/11 10:12:28 by rficht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"

void	minishell(t_prog *ms)
{
	char	*str;
	char	*tmp;

	while (ms->goon)
	{
		tmp = readline("minishell > ");
		str = ft_strtrim(tmp, SPACES);
		if (str && !ft_strequal(str, ""))
		{
			if (ms_parse(str, ms))
			{
				ms_printcmds(*ms);
				//ms_get_fds(ms);
			}
		}
		ms_usual_free(ms, str, tmp);
	}
	printf("exit\n");
}

void	copy_env(char *envp[], t_prog *prog)
{
	char	**envp_copy;
	int		n;

	n = 0;
	envp_copy = calloc(ms_sizeof_tab(envp), sizeof(char *));
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
