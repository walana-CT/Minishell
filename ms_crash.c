/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_crash.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdjemaa <mdjemaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 09:55:29 by rficht            #+#    #+#             */
/*   Updated: 2023/05/05 19:13:22 by mdjemaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"

void	ms_usual_free(t_prog *ms, char *str, char *tmp)
{
	int i;

	i = -1;
	free(str);
	free(tmp);
	while (++i < ms->nbcmd)
	{
		free(ms->cmd[i].line);
		free(ms->cmd);
	}
}

void	ms_free(t_prog *program)
{
	(void) program;
	printf("ms free called\n");
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