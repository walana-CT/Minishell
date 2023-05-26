/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdjemaa <mdjemaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:12:35 by rficht            #+#    #+#             */
/*   Updated: 2023/05/26 22:53:22 by mdjemaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"

static void	ft_sighandle(int sig, siginfo_t *info, void *context)
{
	info = 0;
	context = 0;
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		if (stat_interactive(-1))
			rl_on_new_line();
		rl_redisplay();
	}
}

void	set_sig(void)
{
	struct sigaction	sa;

	sa.sa_flags = SA_RESTART;
	sa.sa_sigaction = ft_sighandle;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		ms_crash(NULL);
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
		ms_crash(NULL);
}
