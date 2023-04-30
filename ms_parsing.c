/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rficht <robin.ficht@free.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 11:52:15 by mdjemaa           #+#    #+#             */
/*   Updated: 2023/04/30 10:13:13 by rficht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"

t_mline	*line_init(char	*str, t_mline *line)
{
	line->tmpcmd = ft_quotesplit(str, '|');
	return (line);
}

void	ms_parse(char *str, t_mline *line)
{
	if (ft_strequal(str, "exit"))
		line->goon = 0;
	else
	{
		line_init(str, line);
		ft_printstrtab(line->tmpcmd, "tmpCmds");
	}
}
