/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rficht <robin.ficht@free.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 11:03:52 by rficht            #+#    #+#             */
/*   Updated: 2023/06/01 11:29:00 by rficht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_toolong(long long nbr, char *str)
{
	if (ft_strlen(str) > 20)
		return (TRUE);
	if (nbr >= 0 && *str == '-')
		return (TRUE);
	if (nbr < 0 && *str != '-')
		return (TRUE);
	return (FALSE);
}

static int	is_long(long int nbr)
{
	if (nbr < -2147483648 || nbr > 2147483647)
		return (TRUE);
	return (FALSE);
}

static int	isdigit_str(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str) && *str != '+' && *str != '-')
			return (FALSE);
		str++;
	}
	return (TRUE);
}

//tputs
int	ms_exit(t_cmd *cmd)
{
	long	return_val;

	printf("\033[1Fmsh > \033[0mexit\n");
	if (!cmd)
	{
		//system("leaks minishell");
		exit(127);
	}
	if (!cmd->args[0])
		return (printf("exit received 0 args\n"), 1);
	if (!cmd->args[1])
		return_val = 127;
	if (!isdigit_str(cmd->args[1]))
		return (ft_putstr_fd(" numeric argument required", 2), 255);
	return_val = ft_atoi(cmd->args[1]);
	if (is_toolong(return_val, cmd->args[1]))
		return (ft_putstr_fd(" numeric argument required", 2), 255);
	if (is_long(return_val))
	{
		if (return_val <= 0)
			return (1);
		return (255);
	}
	if (cmd->args[2])
		return (ft_putstr_fd("exit : too many arguments", 2), 1);
	ms_free(cmd->ms);
	//system("leaks minishell");
	printf("exit\n");
	exit(return_val);
	return (0);
}

