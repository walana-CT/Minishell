/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdjemaa <mdjemaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 16:32:55 by mdjemaa           #+#    #+#             */
/*   Updated: 2023/05/23 19:26:15 by mdjemaa          ###   ########.fr       */
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

typedef struct s_ms
{
	char			**envp;
	int				term_fd;
	char			*line; //la ligne 'de base' retournee par readline
	int				err; // code d'erreur qui sera retourné dans le shell (et dans $?) apres l'execution de line. init à 0 
	int				nbcmd; // nb de commandes
	int				**pipe; // pour pipex
	pid_t			*pid; // pour pipex
	t_cmd			*cmd; // struct necessaire à l'éxécution de la commande par execve()
}	t_ms;

struct s_cmd
{
	char	*line;
	int		nb; // numero de la commande (utile pour pipe ?)
	char	*limiter;
	char	*filein;
	char	*fileout;
	int		*herepipe;
	int		fdin; // dup2(fdin, 0) ; initialiser à 0 ?
	int		fdout; // dup2(fdout, 1) ; initialiser à 1 ?
	char	*cmd_name; // nom de la commande ( = args[0]) pour execve (pas forcément utile en vrai, on peut utiliser args[0])
	char	**args; // arguments de la commande a fournir à execve()
	char	*path; // path à strjoin avec cmd avant de execve()
	t_ms	*ms; //reference du ms pour free
};

//init
void	line_init(char	*str, t_ms *p);
//err and memory
void	ms_crash(t_ms *ms);
void	ms_free(t_ms	*ms);
void	ms_loop_free(t_ms *ms);
int		ms_error_msg(char *str, int err);
int		ms_error_msg_nofile(char *file, int err);
int		ms_bad_child_ending(char *str);

//parsing 1 (line)
int		ms_get_cmds(char *str, t_ms *p);
char	*ms_trim_hashtag(char *str);
int		ms_isquote(char c); // renvoie 1 si c == ', 2  si ", ou 0 sinon
int		*ms_where_are(char c, char *str); // renvoie un tableau de int contenant les index de toutes les occurences de c dans str et se terminant par -1
int		ms_where_is(char c, char *str); // renvoie l'index de la premiere occurence de c dans str , ou -1
int		ms_quote_status(char *str, int j); // renvoie 0, 1 ou 2 selon que str[j] est hors quotes, entre simples quotes ou entre doubles quotes
char	**ms_quotesplit(char *s, char sep);
char	*ms_noquotes(char *str); // retire les quotes et les caracteres entre quotes de str et retourne le resultat
int		ms_str2pipes(char *str); // true si str contient "||"
int		ms_badchev(char *str); // true si str contient "<<<" ou ">>>"
int		ms_pipesplit(t_ms *ms); // split ms.line avec '|" dans cmd[i].line
int		ms_trimquotes(char **str);

//parsing 2 (cmd)
int		ms_get_fds(t_ms *ms);
int		ms_get_fdin(t_cmd *cmd);
int		ms_get_fdout(t_cmd *cmd);
int		dollar_replace(char **str, t_ms *ms);
int		ms_get_limiter(t_cmd *cmd, int i);
int		ms_getappendfd(t_cmd cmd);
int		ms_heredoc(t_cmd *cmd);

//lexing & execution
int		ms_isbuiltin(char *str);
int		ms_lex(t_ms *ms);
int		ms_exec(t_ms *ms);
int		ms_launch_children(t_ms *ms);

//terminal
int		ms_terminal_init(t_ms *ms);
int		ms_terminal_reset(t_ms *ms);
//builtins
int		ms_cd(t_cmd *cmd);
int		ms_exit(t_ms *ms);
int		is_env(char *str, char *env);
int		ms_env(t_cmd *cmd);
int		ms_unset(t_cmd *cmd);
int		ms_echo(t_cmd *cmd);
int		ms_export(t_cmd *cmd);
int		ms_pwd(t_cmd *cmd);
//utils
void	set_sig(void);
int		ms_sizeof_tab(char **my_tab);
void	ms_printtab(char **str_tab, int fd);
int		ms_env_pos(char *str, char **envp);
void	copy_env(char *envp[], t_ms *ms);
char	*ms_getenv(char *str, t_ms *ms);
void	ms_printcmds(t_ms ms);
int		stat_interactive(int val);
int		ms_is_dol_sep(char c);

#endif