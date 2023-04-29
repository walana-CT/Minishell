/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rficht <robin.ficht@free.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 11:36:39 by rficht            #+#    #+#             */
/*   Updated: 2023/04/29 15:46:04 by rficht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../Includes/minishell.h"

//pour les char utiliser des const ou non ??
int	*main(char *str, int n_flag)
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

int arg_valid(int argc, char const *argv[])
(
	
	if (argc == 0)
		return (0);
	if (ft_str)
	{
		/* code */
	}
	ft_
	
)

int main(int argc, char const *argv[])
{
	int n_flag;

	n_flag = 0;
	n_flag_val(argc--, argv++, &n_flag);

	return 0;
}
