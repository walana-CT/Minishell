/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rficht <robin.ficht@free.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 11:08:22 by mdjemaa           #+#    #+#             */
/*   Updated: 2023/04/30 14:37:28 by rficht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"
char	**g_env_lst;

void	minishell(void)
{
	char	*str;
	t_mline	line;

	add_history(str);
	while (line.goon)
	{
		str = readline("minishell > ");
		ms_parse(str, &line);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	(void) argv;
	if (argc > 1)
		printf("minishel doesn't need arguments ;)\n");
	g_env_lst = envp;
	minishell();
	return (0);
}
