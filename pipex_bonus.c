/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rficht <robin.ficht@free.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 12:37:16 by mdjemaa           #+#    #+#             */
/*   Updated: 2023/04/29 15:27:17 by rficht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/pipex_bonus.h"

int	px_end_bonus(t_pipex *p)
{
	int	err;
	int	i;

	i = -1;
	err = 0;
	px_close_pipes_but(p, -1);
	while (++i < p->ncmds)
	{
		ft_freetab(p->args[i]);
		free(p->pipe[i]);
		free(p->cmd[i]);
		waitpid(p->pid[i], &err, 0);
	}
	free(p->pipe);
	free(p->cmd);
	free(p->args);
	free(p->pid);
	ft_freetab(p->paths);
	return (WEXITSTATUS(err));
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	p;

	if (argc < 5 || (ft_strequal(argv[1], "here_doc") && argc < 6))
		return (1);
	px_init_bonus(argc, argv, envp, &p);
	return (px_launch_children(&p, envp));
}
