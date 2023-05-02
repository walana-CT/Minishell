/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rficht <robin.ficht@free.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 11:08:22 by mdjemaa           #+#    #+#             */
/*   Updated: 2023/05/02 12:18:38 by rficht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"
char	**g_env_lst;

void	minishell(void)
{
	char	*str;
	t_mline	line;

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
		printf("received a SIGQUIT (ctrl + C)\n");
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
	set_sig();
	(void) argv;
	if (argc > 1)
		printf("minishel doesn't need arguments ;)\n");
	g_env_lst = envp;
	minishell();
	return (0);
}
