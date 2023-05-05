/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdjemaa <mdjemaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:12:35 by rficht            #+#    #+#             */
/*   Updated: 2023/05/05 14:45:46 by mdjemaa          ###   ########.fr       */
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
