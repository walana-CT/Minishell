/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rficht <robin.ficht@free.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 11:03:02 by rficht            #+#    #+#             */
/*   Updated: 2023/06/01 08:55:16 by rficht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_printtab(char **str_tab, int fd)
{
	while (*str_tab)
	{
		ft_putstr_fd(*str_tab, fd);
		write(fd, "\n", 1);
		str_tab++;
	}
}

int	ms_env(t_cmd *cmd)
{
	t_ms		*ms;

	ms = cmd->ms;
	if (!cmd->args[0])
	{
		printf("env received 0 args\n");
		return (1);
	}
	ms_printtab(ms->envp, cmd->fdout);
	return (0);
}
