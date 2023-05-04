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

typedef struct s_rline	t_rline;
typedef struct s_cmd	t_cmd;

typedef struct s_prog
{
	char 			**envp;
	int				term_fd;
	struct termios	term_original;
	struct termios	term_settings;
	char			*line; //la ligne 'de base' retournee par readline
	int				err; // code d'erreur qui sera retourné dans le shell (et dans $?) apres l'execution de line
	int				goon; // booleen ; faut-il reproposer un prompt apres l'execution de line ? (toujours 1 sauf si exit ou ctrl-C)
	int				nbcmd; // nb de forks à faire ; egal au nombre de pipes dans line + 1
	int				**pipe; // pour pipex
	pid_t			*pid; // pour pipex
	t_cmd			*cmd; // struct necessaire à l'éxécution de la commande par execve()
}	t_prog;

struct s_cmd
{
	char	*line;
	int		fdin; // dup2(fdin, 0) ; initialiser à -1 ?
	int		fdout; // dup2(fdout, 1) ; initialiser à -1 ?
	char	*cmd_name; // nom de la commande ( = args[0]) pour execve (pas forcément utile en vrai, on peut utiliser args[0])
	char	**args; // arguments de la commande a fournir à execve()
	char	*path; // path à strjoin avec cmd avant de execve()
	t_cmd	*prog;//reference du program pour free
};

//init
void	line_init(char	*str, t_prog *p);
//err and memory
void		ms_crash(t_prog *program);
void		ms_free(t_prog	*program);
//parsing
int		ms_checksyntax();
int		ms_parse(char *str, t_prog *p);
int		ms_status(char *str, int i);

//lexing
//terminal
static int		terminal_init(t_prog *program);
static int 		terminal_reset(t_prog *program);
//builtins
int			ms_exit(t_cmd cmd);
//utils
int			sizeof_tab(void **my_tab);


#endif