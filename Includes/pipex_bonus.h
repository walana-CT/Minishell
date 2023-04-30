/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ../Includes/pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rficht <robin.ficht@free.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 12:38:17 by mdjemaa           #+#    #+#             */
/*   Updated: 2023/04/29 15:25:27 by rficht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H
# include <sys/types.h>
# include <sys/uio.h>
# include <sys/wait.h>
# include <stdio.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include "libft.h"
# define RED "\033[31;1m"
# define GREEN "\033[32;1m"
# define YELLOW	"\033[33;1m"
# define RESET "\033[0m"

typedef struct s_pipex	t_pipex;

struct s_pipex
{
	char	*limiter;
	char	*infile;
	char	*outfile;
	int		ncmds;
	pid_t	*pid;
	int		**pipe;
	char	**cmd;
	char	**paths;
	char	***args;
};

int		px_end_bonus(t_pipex *p);
int		px_launch_children(t_pipex *p, char **envp);
void	px_init_bonus(int argc, char **argv, char **envp, t_pipex *p);
int		px_file_err(char *file);
char	*px_prefix_cmd(char *cmd, char **path);
char	**px_get_path(char **envp);
void	px_get_outfile(t_pipex *p);
void	px_close_pipes_but(t_pipex *p, int a);
void	px_bad_child_ending(char *str);

#endif