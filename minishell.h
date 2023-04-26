/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdjemaa <mdjemaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 11:08:55 by mdjemaa           #+#    #+#             */
/*   Updated: 2023/04/26 15:24:49 by mdjemaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <signal.h>
# include "libft/libft.h"

typedef struct s_mline	t_mline;
typedef struct s_cmd	t_cmd;

struct s_mline
{
	int		err;
	int		goon;
	int		nbcmd;
	int		**pipe;
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