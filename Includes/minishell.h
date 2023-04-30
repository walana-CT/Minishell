/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ../Includes/minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rficht <robin.ficht@free.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 15:13:07 by rficht            #+#    #+#             */
/*   Updated: 2023/04/29 15:21:02 by rficht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <curses.h>
# include <dirent.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/param.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <term.h>
# include <unistd.h>
# include "libft.h"

# define FALSE	0
# define TRUE	1

typedef struct s_mline	t_mline;
typedef struct s_cmd	t_cmd;

typedef struct s_program
{
	int				term_fd;
	struct termios	term_original;
	struct termios	term_settings;
}	t_program;

struct s_mline
{
	int		err;
	int		goon;
	int		nbcmd;
	int		**pipe;
	char	**tmpcmd;
	pid_t	*pid;
	t_cmd	*cmd;
};

struct s_cmd
{
	int		fdin;
	int		fdout;
	char	*cmd;
	char	**args;
	char	*path;
};

t_mline	*line_init(char	*str, t_mline *line);
void	ms_parse(char *str, t_mline *line);

#endif