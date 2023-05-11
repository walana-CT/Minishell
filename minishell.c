/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdjemaa <mdjemaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 11:08:22 by mdjemaa           #+#    #+#             */
/*   Updated: 2023/05/11 11:19:47 by mdjemaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"

void	minishell(t_prog *ms)
{
	char	*str;
	char	*tmp;

	while (ms->goon)
	{
		tmp = readline("msh > ");
		str = ft_strtrim(tmp, SPACES);
		if (str && !ft_strequal(str, ""))
		{
			if (ms_parse(str, ms))
			{
				ms_get_fds(ms);
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
	envp_copy = malloc(ms_sizeof_tab(envp) * sizeof(char *));
	if (!envp_copy)
		ms_crash(NULL);
	while (envp[n])
	{
		envp_copy[n] = ft_strdup(envp[n]);
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
	{
		if (errno == ENOTTY)
			fprintf(stderr, "This program requires a terminal.\n");
		else
			fprintf(stderr, "Cannot initialize terminal: %s.\n", strerror(errno));
		return (EXIT_FAILURE);
	}
	(void) argv;
	if (argc > 1)
		printf("minishell doesn't need arguments ;)\n");
	minishell(&ms);
	//system("leaks minishell");
	return (0);
}
