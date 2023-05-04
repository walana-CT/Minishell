/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rficht <robin.ficht@free.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 11:08:22 by mdjemaa           #+#    #+#             */
/*   Updated: 2023/05/04 16:12:53 by rficht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"

void	minishell(t_prog ms)
{
	char	*str;

	add_history(str);
	while (1)
	{
		str = readline("minishell > ");
		ms_parse(str, &ms);
	}
	printf("exit\n");
}

void	copy_env(char *envp[], t_prog *prog)
{
	char **envp_copy;
	int n;

	n = 0;
	envp_copy = malloc(sizeof_tab(envp) * sizeof(char *));
	if (!envp_copy)
		ms_crash(NULL);
	while (envp[n])
	{
		envp_copy[n] = envp[n];
		n++;
	}
	prog->envp = envp_copy;	
}

int	main(int argc, char *argv[], char *envp[])
{
	t_prog	ms;

	set_sig();
	copy_env(envp, &ms);
	if (terminal_init(&ms))
	{
		if (errno == ENOTTY)
			fprintf(stderr, "This program requires a terminal.\n");
		else
			fprintf(stderr, "Cannot initialize terminal: %s.\n", strerror(errno));
		return EXIT_FAILURE;
	}
	(void) argv;
	if (argc > 1)
		printf("minishel doesn't need arguments ;)\n");
	minishell(ms);
	return (0);
}
