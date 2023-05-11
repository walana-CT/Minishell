/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redirect_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdjemaa <mdjemaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 12:53:26 by mdjemaa           #+#    #+#             */
/*   Updated: 2023/05/10 16:47:09 by mdjemaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"

/*
void	ms_get_infile(t_pipex *p, char **argv)
{
	char	*str;

	if (p->limiter)
	{
		str = get_next_line(0);
		while (ft_strncmp(str, p->limiter, ft_sstrlen(str)) != 10)
		{		
			write(p->pipe[0][1], str, ft_sstrlen(str));
			free(str);
			str = get_next_line(0);
		}
		free(str);
		close(p->pipe[0][1]);
	}
	else
	{
		p->pipe[0][0] = open(argv[1], O_RDONLY);
		if (p->pipe[0][0] == -1)
			px_file_err(argv[1]);
	}
}
*/
int	ms_get_limiter(t_cmd *cmd, int i)
{
	int	delstart;
	int	start;

	delstart = i - 2;
	while (cmd->line[i] == ' ')
		i++;
	start = i;
	if (ft_is_in(cmd->line[i], FORBID_HEREDOC) >= 0)
		return (0);
	while (cmd->line[i] && ft_is_in(cmd->line[i], END_HEREDOC) == -1)
		i++;
	cmd->limiter = ft_substr(cmd->line, start, i - start);
	// ft_trimquotes(ft_dollar_replace(cmd->filein);
	ft_strdelnfrom(cmd->line, delstart, i - delstart);
	return (1);
}
