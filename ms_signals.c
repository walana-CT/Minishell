/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rficht <robin.ficht@free.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:12:35 by rficht            #+#    #+#             */
/*   Updated: 2023/05/11 17:00:29 by rficht           ###   ########.fr       */
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
		exit(EXIT_FAILURE);
	}
}

void	set_sig(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = ft_sighandle;
	//.sa_mask = SIGQUIT;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		ms_crash(NULL);
}
