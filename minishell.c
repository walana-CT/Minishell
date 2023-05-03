/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdjemaa <mdjemaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 11:08:22 by mdjemaa           #+#    #+#             */
/*   Updated: 2023/05/03 14:34:59 by mdjemaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"

void	minishell(t_prog ms)
{
	char	*str;

	add_history(str);
	while (ms.goon)
	{
		str = readline("minishell > ");
		ms_parse(str, &ms);
	}
}

static void	ft_sighandle(int sig, siginfo_t *info, void *context)
{
	info = 0;
	context = 0;
	if (sig == SIGINT)
	{
		printf("received a SIGINT (ctrl + C)\n");
	}
	if (sig == SIGQUIT)
	{
		printf("received a SIGQUIT (ctrl + \\)\n");
	}
}

static void	ms_crash(char *str)
{
	printf("%s\n", str);
}

static void	set_sig(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = ft_sighandle;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		ms_crash("SIGINT assignation failed\n");
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
		ms_crash("SIGQUIT assignation failed\n");
}

static int	terminal_init(t_prog *ms)
{
	(void) ms;
	return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_prog	ms;

	ms.envp = envp;
	set_sig();
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
