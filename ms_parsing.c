/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdjemaa <mdjemaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 11:52:15 by mdjemaa           #+#    #+#             */
/*   Updated: 2023/04/26 15:25:06 by mdjemaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_mline	*line_init(char	*str, t_mline *line)
{
	(void) str;
	return (line);
}

void	ms_parse(char *str, t_mline *line)
{
	if (ft_strequal(str, "exit"))
		line->goon = 0;
	else
	{
		line_init(str, line);
	}
}
