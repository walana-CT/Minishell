/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rficht <robin.ficht@free.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 11:36:39 by rficht            #+#    #+#             */
/*   Updated: 2023/04/29 11:58:05 by rficht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

//pour les char utiliser des const ou non ??
int	*ms_echo(char *str, int n_flag)
{
	int	n;

	while (str[n])
		n++;
	if (write(1, str, n) == -1)
		return (1);
	if (n > 0)
	{
		if (n_flag == FALSE && str[n - 1] != '\c')
			if (write(1, "\n", 1) == -1)
				return (1);
	}
	else if (n_flag == FALSE)
	{
		if (write(1, "\n", 1) == -1)
			return (1);
	}
	return (0);
}
