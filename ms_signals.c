/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rficht <robin.ficht@free.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:12:35 by rficht            #+#    #+#             */
/*   Updated: 2023/05/31 11:47:25 by rficht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"

static void	ft_sighandle(int sig, siginfo_t *info, void *context)
{
	info = 0;
	context = 0;
	if (sig == SIGINT)
	{
		if (stat_sig(-1) == disabled)
			return ;
		if (stat_sig(-1) == child)
		{
			exit (4);
		}
		write(1, "\n", 1);
		rl_replace_line("", 0);
		if (stat_sig(-1) == prompt)
		{
			rl_on_new_line();
		}
		rl_redisplay();
		stat_err(1);
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
