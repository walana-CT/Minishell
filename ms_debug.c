/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_debug.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rficht <robin.ficht@free.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:32:05 by rficht            #+#    #+#             */
/*   Updated: 2023/05/26 15:55:38 by rficht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_printcmds(t_ms ms)
{
	int	i;

	i = -1;
	printf("Nb commandes %d\n", ms.nbcmd);
	while (++i < ms.nbcmd)
	{
		printf(YELLOW"commande %d\n"RESET, ms.cmd[i].nb);
		ft_printstrtab(ms.cmd[i].args, "ARGS");
		printf("PATH : %s\n", ms.cmd[i].path);
		printf("Filein : %s \t fdin %d\n", ms.cmd[i].filein, ms.cmd[i].fdin);
		printf("Fileout : %s \t fdout %d\n", ms.cmd[i].fileout, ms.cmd[i].fdout);
		printf("Pipein %d \t Pipeout %d\n", ms.pipe[i][0], ms.pipe[i][1]);
	}
}

/**
 * debug function that print pipes with their respectives in and out.
 * @param ms address of minishell.
 */
void	ms_disp_pipes(t_ms *ms)
{
	int	i;

	i = -1;
	printf("Pipes are :\n");
	while (++i < ms->nbcmd - 1)
		printf("Pipe %d : [0]%d [1]%d\n", i, ms->pipe[i][0], ms->pipe[i][1]);
}

