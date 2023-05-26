/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redirect_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rficht <robin.ficht@free.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 12:53:26 by mdjemaa           #+#    #+#             */
/*   Updated: 2023/05/26 16:16:37 by rficht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"

/**
 * define the liniter if we encounter a << symbol.
 * @param cmd a struct cmd.
 * @param i index of char after the << symbol.
 * @return return 0 or 1 or whether if the Heredoc is valid or not. 
 */
int	ms_get_limiter(t_cmd *cmd, int i)
{
	int	delstart;
	int	start;

	delstart = i - 2;
	while (cmd->line[i] == ' ')
		i++;
	start = i;
	if (ft_is_in(cmd->line[i], FORBID_HEREDOC) >= 0)
		return (1);
	while (cmd->line[i] && ft_is_in(cmd->line[i], END_HEREDOC) == -1)
		i++;
	cmd->limiter = ft_substr(cmd->line, start, i - start);
	if (!cmd->limiter || !cmd->line)
		ms_crash(cmd->ms);
	ft_strdelnfrom(&cmd->line, delstart, i - delstart);
	ms_trimquotes(&cmd->limiter);
	if (!cmd->limiter)
		ms_crash(cmd->ms);
	return (0);
}

int	ms_getappendfd(t_cmd cmd)
{
	int		fd;
	char	str[1000];

	fd = open(cmd.fileout, O_CREAT | O_RDWR, 0644);
	if (fd == -1)
		ms_crash(cmd.ms);
	while (read(fd, &str, 1000))
		;
	return (fd);
}

/**
 * Interprete the filename given as input and output as Filedescriptors.
 * @param ms address of minishell.
 * @return return 0 or 1 or whether if the filenames are valids or not. 
 */
int	ms_get_fds(t_ms *ms)
{
	int	i;

	i = -1;
	while (++i < ms->nbcmd)
	{
		if (ms_get_fdin(&(ms->cmd[i])) || ms_get_fdout(&(ms->cmd[i])))
			return (1);
	}
	return (0);
}

int	ms_heredoc(t_cmd *cmd)
{
	char	*str;

	cmd->herepipe = malloc(2 * sizeof(int));
	if (!cmd->herepipe || pipe(cmd->herepipe) == -1)
		return (1);
	stat_interactive(1);
	str = get_next_line(0);
	while (ft_strncmp(str, cmd->limiter, ft_sstrlen(str)) != 10)
	{
		if (!ms_dollar_replace(&str, cmd->ms))
			write(cmd->herepipe[1], str, ft_sstrlen(str));
		free(str);
		str = get_next_line(0);
	}
	free(str);
	close(cmd->herepipe[1]);
	stat_interactive(0);
	cmd->fdin = cmd->herepipe[0];
	return (0);
}
