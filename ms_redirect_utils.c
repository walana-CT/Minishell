/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redirect_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdjemaa <mdjemaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 12:53:26 by mdjemaa           #+#    #+#             */
/*   Updated: 2023/05/11 18:30:32 by mdjemaa          ###   ########.fr       */
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
	ft_strdelnfrom(cmd->line, delstart, i - delstart);
	ms_trimquotes(cmd->limiter);
	return (1);
}

int	ms_getappendfd(t_cmd cmd)
{
	int		fd;
	char	str[1000];

	fd = open(cmd.fileout, O_CREAT | O_RDWR, 0644);
	while (read(fd, &str, 1000))
		;
	return (fd);
}

int	ms_get_fds(t_prog *ms)
{
	int	i;

	i = -1;
	while (++i < ms->nbcmd)
	{
		if (!ms_get_fdin(&(ms->cmd[i])) || !ms_get_fdout(&(ms->cmd[i])))
			return (FALSE);
		printf("commande 'pure' %s\n", ms->cmd[i].line);
	}
	return (TRUE);
}

void	ms_heredoc(t_cmd cmd)
{
	char	*str;

	str = get_next_line(0);
	while (ft_strncmp(str, cmd.limiter, ft_sstrlen(str)) != 10)
	{
		write(cmd.prog->pipe[cmd.nb][1], str, ft_sstrlen(str));
		free(str);
		str = get_next_line(0);
	}
	free(str);
	close(cmd.prog->pipe[cmd.nb][1]);
}