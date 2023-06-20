/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexing_01.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rficht <robin.ficht@free.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 15:30:38 by rficht            #+#    #+#             */
/*   Updated: 2023/06/20 15:31:46 by rficht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ms_getpath(t_ms *ms)
{
	int		i;

	i = -1;
	while (ms->envp[++i])
		if (ft_strnstr(ms->envp[i], "PATH=", 5))
			return (ms_quotesplit(ms->envp[i] + 5, ':', ms));
	return (0);
}
