/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rficht <robin.ficht@free.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 11:08:22 by mdjemaa           #+#    #+#             */
/*   Updated: 2023/05/02 17:59:52 by rficht           ###   ########.fr       */
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
		ms_parse(str, &line);
	}
}

static void	ft_sighandle(int sig, siginfo_t *info, void *context)
{
	if (sig == SIGINT)
	{
		printf("received a SIGINT (ctrl + C)\n");
	}
	if (sig == SIGQUIT)
	{
		printf("received a SIGQUIT (ctrl + \\)\n");
	}
}

static void	set_sig(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = ft_sighandle;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		ft_crash("SIGINT assignation failed\n");
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
		ft_crash("SIGQUIT assignation failed\n");
}



int	main(int argc, char *argv[], char *envp[])
{
	t_prog	ms;

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
