/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rficht <robin.ficht@free.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 11:20:11 by mdjemaa           #+#    #+#             */
/*   Updated: 2023/05/23 11:05:25 by rficht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"

int	ms_wrongchars(char	*str)
{
	int	i;
	int	last;

	last = ft_sstrlen(str) - 1;
	if (ms_str2pipes(str) || str[0] == '|' || str[last] == '|')
		return (ms_error_msg(SYN_EUNEXT"|", TRUE));
	if (ms_badchev(str) || str[last] == '<' || str[last] == '>')
		return (ms_error_msg(SYN_EUNEXT"< or >", TRUE));
	i = -1;
	while (str[++i])
		if (!ms_quote_status(str, i) && ft_is_in(str[i], FORBID_CHAR) != -1)
			return (ms_error_msg(SYN_EUNEXT FORBID_CHAR, TRUE));
	return (FALSE);
}

int	ms_openquotes(char *str)
{
	int		open;
	int		i;
	char	quote;

	i = -1;
	open = 0;
	while (str[++i])
	{
		if (!open && ms_isquote(str[i]))
		{
			quote = str[i];
			open = 1;
		}
		else if (str[i] == quote)
			open = 0;
	}
	return (open);
}

/**
 * return TRUE or FALSE depending on whether the line is valid or not.
 * @param str line of commande after spaces have been trimed.
 */
int	ms_syntax_ok(char *str)
{
	if (ms_openquotes(str))
	{
		return (ms_error_msg("unexpected EOF while looking\
			for matching `\"\' ", FALSE));
	}
	if (ms_wrongchars(str))
		return (FALSE);
	return (TRUE);
}

void	ms_disp_pipes(t_ms *ms)
{
	int	i;

	i = -1;
	printf("Pipes are :\n");
	while (++i < ms->nbcmd - 1)
		printf("Pipe %d : [0]%d [1]%d\n", i, ms->pipe[i][0], ms->pipe[i][1]);
}

int	ms_pipe_init(t_ms *ms)
{
	int	i;

	if (ms->nbcmd < 2)
	{
		ms->pipe = 0;
		return (0);
	}
	ms->pipe = malloc((ms->nbcmd - 1) * sizeof(int *));
	if (!ms->pipe)
		return (1);
	i = -1;
	while (++i < ms->nbcmd - 1)
	{
		ms->pipe[i] = malloc(2 * sizeof(int));
		if (!ms->pipe[i] || pipe(ms->pipe[i]) == -1)
			return (1);
	}
	return (0);
}

/**
 * Separate the str line based on the | symboles.
 * @param ms address of minishell.
 * @return return 0 in case of success otherwise return 1.
 */
int	ms_cmds_init(t_ms *ms)
{
	int	i;

	i = -1;
	ms->nbcmd = ms_pipesplit(ms);
	if (ms->nbcmd == -1)
		return (1);
	while (++i < ms->nbcmd)
	{
		ms->cmd[i].nb = i;
		ms->cmd[i].args = 0;
		ms->cmd[i].cmd_name = 0;
		ms->cmd[i].fdin = 0;
		ms->cmd[i].filein = 0;
		ms->cmd[i].fileout = 0;
		ms->cmd[i].fdout = 1;
		ms->cmd[i].limiter = 0;
		ms->cmd[i].path = 0;
		ms->cmd[i].ms = ms;
	}
	ms_pipe_init(ms);
	// ms_disp_pipes(ms);
	return (0);
}

/**
 * verify if the line is valid or not turn the line into an array of struct cmd.
 * set err val. Alloc errors calls exit(). 
 * @param str line of commande after spaces have been trimed.
 * @param ms address of minishell.
 * @return return TRUE or FALSE depending on whether the line is valid or not.
 */
int	ms_parse(char *str, t_ms *ms)
{
	ms->line = str;
	if (!ms_syntax_ok(ms->line))
	{
		ms->err = 258;
		return (FALSE);
	}
	if (ms_cmds_init(ms))
		return (FALSE);
	return (TRUE);
}
