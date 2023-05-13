/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdjemaa <mdjemaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 16:32:55 by mdjemaa           #+#    #+#             */
/*   Updated: 2023/05/13 21:45:21 by mdjemaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <curses.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
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
# define SYN_EUNEXT "msh : syntax error near unexpected token "
# define SPACES "\t\n\v\f\r "
# define END_REDIR " #<>\0"
# define FORBID_REDIR "#<>|"
# define END_HEREDOC " #<>|\0"
# define FORBID_HEREDOC "#<>|"
# define FORBID_CHAR "\\;()[]&"
# define NO_F ": No such file or directory\n"

typedef struct s_cmd	t_cmd;

typedef struct s_prog
{
	char			**envp;
	int				term_fd;
	struct termios	term_original;
	struct termios	term_settings;
	char			*line; //la ligne 'de base' retournee par readline
	int				err; // code d'erreur qui sera retourné dans le shell (et dans $?) apres l'execution de line. init à 0 
	int				goon; // booleen ; faut-il reproposer un prompt apres l'execution de line ? (toujours 1 sauf si exit ou ctrl-C)
	int				nbcmd; // nb de forks à faire ; egal au nombre de pipes dans line + 1
	int				**pipe; // pour pipex
	pid_t			*pid; // pour pipex
	t_cmd			*cmd; // struct necessaire à l'éxécution de la commande par execve()
}	t_prog;

struct s_cmd
{
	char	*line;
	int		nb; // numero de la commande (utile pour pipe ?)
	char	*limiter;
	char	*filein;
	char	*fileout;
	int		fdin; // dup2(fdin, 0) ; initialiser à 0 ?
	int		fdout; // dup2(fdout, 1) ; initialiser à 1 ?
	char	*cmd_name; // nom de la commande ( = args[0]) pour execve (pas forcément utile en vrai, on peut utiliser args[0])
	char	**args; // arguments de la commande a fournir à execve()
	char	*path; // path à strjoin avec cmd avant de execve()
	t_prog	*prog; //reference du program pour free
};

//init
void	line_init(char	*str, t_prog *p);
//err and memory
void	ms_crash(t_prog *program);
void	ms_free(t_prog	*program);
void	ms_usual_free(t_prog *ms, char **str, char **tmp);
int		ms_error_msg(char *str, int err);
int		ms_error_msg_nofile(char *file, int err);

//parsing 1 (line)
int		ms_parse(char *str, t_prog *p);
int		ms_isquote(char c); // renvoie 1 si c == ', 2  si ", ou 0 sinon
int		*ms_where_are(char c, char *str); // renvoie un tableau de int contenant les index de toutes les occurences de c dans str et se terminant par -1
int		ms_where_is(char c, char *str); // renvoie l'index de la premiere occurence de c dans str , ou -1
int		ms_quote_status(char *str, int j); // renvoie 0, 1 ou 2 selon que str[j] est hors quotes, entre simples quotes ou entre doubles quotes
char	**ms_quotesplit(char *s, char sep);
char	*ms_noquotes(char *str); // retire les quotes et les caracteres entre quotes de str et retourne le resultat
int		ms_str2pipes(char *str); // true si str contient "||"
int		ms_badchev(char *str); // true si str contient "<<<" ou ">>>"
int		ms_pipesplit(t_prog *ms); // split ms.line avec '|" dans cmd[i].line
void	ms_trimquotes(char *str);

//parsing 2 (cmd)
int		ms_get_fds(t_prog *ms);
int		ms_get_fdin(t_cmd *cmd);
int		ms_get_fdout(t_cmd *cmd);
int		dollar_replace(char **str, t_prog *prog);
int		ms_get_limiter(t_cmd *cmd, int i);
int		ms_getappendfd(t_cmd cmd);
void	ms_heredoc(t_cmd cmd);

//lexing & execution
int		ms_isbuiltin(char *str);
int		ms_lex(t_prog *ms);
void	ms_exec(t_prog *ms);

//terminal
int		terminal_init(t_prog *program);
int		terminal_reset(t_prog *program);
//builtins
int		ms_cd(t_cmd *cmd);
int		ms_exit(t_cmd *cmd);
int		is_env(char *str, char *env);
int		ms_env(t_cmd *cmd);
int		ms_unset(t_cmd *cmd);
int		ms_echo(t_cmd *cmd);
int		ms_export(t_cmd *cmd);
int		ms_pwd(t_cmd *cmd);
//utils
void	set_sig(void);
int		ms_sizeof_tab(char **my_tab);
int		ms_env_pos(char *str, char **envp);
char	*ms_getenv(char *str, t_prog *prog);
void	ms_printcmds(t_prog ms);

#endif