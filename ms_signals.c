/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rficht <robin.ficht@free.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:12:35 by rficht            #+#    #+#             */
/*   Updated: 2023/05/04 13:44:54 by rficht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"

static void	ft_sighandle(int sig, siginfo_t *info, void *context)
{
	info = 0;
	context = 0;
	if (sig == SIGINT)
	{
		printf("received a SIGINT (ctrl + C)\n");
		rl_on_new_line();
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
		ms_crash("SIGINT assignation failed\n");
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
		ms_crash("SIGQUIT assignation failed\n");
}