/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rficht <robin.ficht@free.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 11:03:02 by rficht            #+#    #+#             */
/*   Updated: 2023/05/15 15:17:44 by rficht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"

int	ms_env(t_cmd *cmd)
{
	char		**envp;
	t_ms		*ms;

	ms = cmd->ms;
	if (!cmd->args[0])
	{
		printf("env received 0 args\n");
		return (1);
	}
	envp = ms->envp;
	while (*envp)
	{
		printf("%s\n", *envp);
		envp++;
	}
	return (0);
}
