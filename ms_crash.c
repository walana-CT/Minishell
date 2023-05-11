/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_crash.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rficht <robin.ficht@free.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 09:55:29 by rficht            #+#    #+#             */
/*   Updated: 2023/05/11 11:51:58 by rficht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"



void	ms_usual_free(t_prog *ms, char *str, char *tmp)
{
	int	i;

	i = -1;
	if (str)
		free(str);
	if (tmp)
		free(tmp);
	while (++i < ms->nbcmd)
		free(ms->cmd[i].line);
	if (ms->nbcmd)
		free(ms->cmd);
}

void	ms_free(t_prog *program)
{
	int	n;

	n = 0;
	printf("ms free called\n");
	if (program->envp)
	{
		while (program->envp[n])
			ft_freestr(program->envp[n++]);
	}
}

void	ms_crash(t_prog *program)
{
	if (program)
		ms_free(program);
	perror("minishell : ");
}

int	ms_error_msg(char *str, int err)
{
	write(2, str, ft_sstrlen(str));
	write(2, "\n", 1);
	return (err);
}
