/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdjemaa <mdjemaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 11:08:22 by mdjemaa           #+#    #+#             */
/*   Updated: 2023/05/02 14:24:58 by mdjemaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"

void	minishell(t_program ms)
{
	char	*str;
	t_rline	line;

	add_history(str);
	while (line.goon)
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
	t_program	ms;

	set_sig();
	(void) argv;
	if (argc > 1)
		printf("minishel doesn't need arguments ;)\n");
	g_env_lst = envp;
	minishell(ms);
	return (0);
}
