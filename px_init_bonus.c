/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_init_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdjemaa <mdjemaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 15:40:06 by mamat             #+#    #+#             */
/*   Updated: 2023/03/30 15:42:24 by mdjemaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	px_init_pipes(t_pipex *p, int argc)
{
	int	i;

	i = -1;
	p->ncmds = argc - 3;
	if (p->limiter)
		p->ncmds--;
	p->pipe = malloc(p->ncmds * sizeof(int *));
	while (++i < p->ncmds)
	{
		p->pipe[i] = malloc(2 * sizeof(int));
		if (pipe(p->pipe[i]) == -1)
			exit(1);
	}
}

void	px_get_infile(t_pipex *p, char **argv)
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

void	px_get_outfile(t_pipex *p)
{
	char	str[100];

	if (p->limiter)
	{
		p->pipe[p->ncmds - 1][1] = open(p->outfile, O_CREAT | O_RDWR, 0644);
		if (p->pipe[p->ncmds - 1][1] == -1)
			exit(px_file_err(p->outfile));
		while (read(p->pipe[p->ncmds - 1][1], &str, 100))
			;
	}
	else
		p->pipe[p->ncmds - 1][1] = open(p->outfile,
				O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (p->pipe[p->ncmds - 1][1] == -1)
		exit(px_file_err(p->outfile));
}

void	px_init_bonus(int argc, char **argv, char **envp, t_pipex *p)
{
	int	i;

	p->limiter = 0;
	if (ft_strequal(argv[1], "here_doc"))
		p->limiter = argv[2];
	p->outfile = argv[argc - 1];
	px_init_pipes(p, argc);
	px_get_infile(p, argv);
	p->paths = px_get_path(envp);
	i = -1;
	p->pid = malloc(sizeof(int) * p->ncmds);
	p->cmd = malloc(sizeof(char *) * p->ncmds);
	p->args = malloc(sizeof(char *) * p->ncmds);
	while (++i < p->ncmds)
	{
		p->args[i] = ft_quotesplit(argv[argc - p->ncmds + i - 1], ' ');
		p->cmd[i] = px_prefix_cmd(p->args[i][0], p->paths);
	}
}
