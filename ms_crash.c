/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_crash.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rficht <robin.ficht@free.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 09:55:29 by rficht            #+#    #+#             */
/*   Updated: 2023/05/15 15:17:44 by rficht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"



/*void	ms_usual_free(t_ms *ms, char *str, char *tmp)
{
	int	i;

	i = -1;
	ft_freestr(&str);
	ft_freestr(&tmp);
	while (++i < ms->nbcmd)
	{
		ft_freestr(&(ms->cmd[i].line));
		if (ms->cmd[i].fdin != 0)
			close(ms->cmd[i].fdin);
		if (ms->cmd[i].fdout != 1)
			close(ms->cmd[i].fdout);
		if (ms->cmd[i].filein)
			free(ms->cmd[i].filein);
		if (ms->cmd[i].fileout)
			free(ms->cmd[i].fileout);
	}
	if (ms->nbcmd)
		ft_freenull((void **) &ms->cmd);
	ms->nbcmd = 0;
}

void	ms_free(t_ms *ms)
{
	int	n;

	n = 0;
	printf("ms free called\n");
	if (ms->envp)
	{
		ms_terminal_reset(ms);
		while (ms->envp[n])
			ft_freestr(&ms->envp[n++]);
	}
}*/

void	ms_crash(t_ms *ms)
{
	if (ms)
		ms_free(ms);
	perror("msh : ");
	exit(errno);
}

int	ms_error_msg(char *str, int err)
{
	write(2, str, ft_sstrlen(str));
	write(2, "\n", 1);
	return (err);
}

int	ms_error_msg_nofile(char *file, int err)
{
	write(2, "msh: ", 5);
	write(2, file, ft_sstrlen(file));
	write(2, NO_F"\n", 28);
	return (err);
}
