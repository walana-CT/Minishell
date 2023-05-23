/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rficht <robin.ficht@free.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 16:32:55 by mdjemaa           #+#    #+#             */
/*   Updated: 2023/05/23 16:33:30 by rficht           ###   ########.fr       */
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
	char		**envp;
	int			term_fd;
	char		*line;
	int			err;
	int			nbcmd;
	int			**pipe;
	pid_t		*pid;
	t_cmd		*cmd;
}	t_ms;

struct s_cmd
{
	char		*line;
	int			nb;
	char		*limiter;
	char		*filein;
	char		*fileout;
	int			fdin;
	int			fdout;
	char		*cmd_name;
	char		**args;
	char		*path;
	t_ms		*ms;
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
int		ms_isquote(char c);
int		*ms_where_are(char c, char *str);
int		ms_where_is(char c, char *str);
int		ms_quote_status(char *str, int j);
char	**ms_quotesplit(char *s, char sep);
char	*ms_noquotes(char *str);
int		ms_str2pipes(char *str);
int		ms_badchev(char *str);
int		ms_pipesplit(t_ms *ms);
int		ms_trimquotes(char **str);

//parsing 2 (cmd)

int		ms_get_fds(t_ms *ms);
int		ms_get_fdin(t_cmd *cmd);
int		ms_get_fdout(t_cmd *cmd);
int		dollar_replace(char **str, t_ms *ms);
int		ms_get_limiter(t_cmd *cmd, int i);
int		ms_getappendfd(t_cmd cmd);
void	ms_heredoc(t_cmd cmd);

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
//debug

void	ms_printcmds(t_ms ms);

#endif