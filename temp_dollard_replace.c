/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp_dollard_replace.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rficht <robin.ficht@free.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:24:46 by rficht            #+#    #+#             */
/*   Updated: 2023/05/05 17:27:10 by rficht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"

char *ms_getenv(char *str, t_prog *prog)
{
	
}


char *dol_replace(char *str, int pos, t_prog *prog)
{
	char	*env_var;
	char	*env_line;
	int		i;
	int		j;

	i = 0;
	while (str[i + pos] && str[i + pos] != ' ')
		env_var[j++] = str[i++];
	env_var = ft_calloc(j + 1, sizeof(char));
	i = pos + 1;
	j = 0;
	while (str[i] && str[i] != ' ')
		env_var[j++] = str[i++];
	env_line = ms_getenv(env_var, prog->envp);
	env_var_val = ms_getenv;

}


int	next_dol_pos(char *str)
{
	int	n;

	while (str[n])
	{
		if (str[n] == '$' && ms_quote_status(str, n) != 1)
			return (n);
		n++;
	}
	return (-1);
}


char *dollard_replace(char *str, t_prog *prog)
{
	int	dol_pos;

	dol_pos = next_dol_pos(str);
	while (dol_pos != -1)
	{
		str = dol_replace(str, dol_pos, prog);
	}
	
}