/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdjemaa <mdjemaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 11:52:15 by mdjemaa           #+#    #+#             */
/*   Updated: 2023/05/02 14:55:55 by mdjemaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"

int	*ms_status(char *str)
{
	int	*status;
	int	i;
	int	size;

	i = -1;
	size = ft_sstrlen(str);
	status = malloc(sizeof(int) * size);
	while (i <  )
}

void	rline_init(char	*str, t_rline *rl)
{
	rl->line = str;
	rl->size = ft_sstrlen(str);
	rl->status = ms_status(str);
}

void	ms_parse(char *str, t_rline *rl)
{
	if (ft_strequal(str, "exit"))
		rl->goon = 0;
	else
	{
		rline_init(str, rl);
		ft_printstrtab(rl->line, "tmpCmds");
	}
}
