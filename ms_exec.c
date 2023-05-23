/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rficht <robin.ficht@free.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 20:28:47 by mdjemaa           #+#    #+#             */
/*   Updated: 2023/05/22 16:04:13 by rficht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"

int	ms_do_builtin(t_cmd	*cmd)
{
	if (ft_strequal(cmd->cmd_name, "cd"))
		return (ms_cd(cmd));
	if (ft_strequal(cmd->cmd_name, "echo"))
		return (ms_echo(cmd));
	if (ft_strequal(cmd->cmd_name, "env"))
		return (ms_env(cmd));
	if (ft_strequal(cmd->cmd_name, "exit"))
		return (ms_exit(cmd->ms));
	if (ft_strequal(cmd->cmd_name, "export"))
		return (ms_export(cmd));
	if (ft_strequal(cmd->cmd_name, "pwd"))
		return (ms_pwd(cmd));
	if (ft_strequal(cmd->cmd_name, "unset"))
		return (ms_unset(cmd));
	return (0);
}

void	ms_fixfds(t_cmd	*cmd)
{
	int	i;

	i = cmd->nb;
	if (!cmd->filein)
	{
		if (i == 0)
			cmd->fdin = 0;
		else
			cmd->fdin = cmd->ms->pipe[i - 1][0];
	}
	if (!cmd->fileout)
	{
		if (i == cmd->ms->nbcmd - 1)
			cmd->fdout = 1;
		else
			cmd->fdout = cmd->ms->pipe[i][1];
	}
}

void	ms_printcmd(t_cmd cmd)
{
	printf(YELLOW"commande %d\n"RESET, cmd.nb);
	ft_printstrtab(cmd.args, "ARGS");
	printf("PATH : %s\n", cmd.path);
	printf("CmdName : %s\n", cmd.cmd_name);
	printf("Filein : %s \t fdin %d\n", cmd.filein, cmd.fdin);
	printf("Fileout : %s \t fdout %d\n", cmd.fileout, cmd.fdout);
	printf("_____________________________________________\n");
}

void	ms_close_pipes_but(t_ms *ms, int i)
{
	int	j;

	j = -1;
	printf("Cmd %d ", i);
	while (++j < ms->nbcmd - 1)
	{
		if (j != i - 1)
			close(ms->pipe[j][0]);
		if (j != i)
			close(ms->pipe[j][1]);
	}
}

void	ms_child(t_ms *ms, int i)
{
	char	*pathcmd;

	rl_catch_signals = 1;
	ms_close_pipes_but(ms, i);
	ms_fixfds(&ms->cmd[i]);
	// printf("process reads on %d and writes on %d\n", ms->cmd[i].fdin, ms->cmd[i].fdout);
	dup2(ms->cmd[i].fdin, 0);
	dup2(ms->cmd[i].fdout, 1);
	if (ms_isbuiltin(ms->cmd[i].cmd_name))
		exit(ms_do_builtin(&ms->cmd[i]));
	else
	{
		// ms_printcmd(ms->cmd[i]);
		pathcmd = ft_strmanyjoin(ms->cmd[i].path, "/", ms->cmd[i].cmd_name, 0);
		execve(pathcmd, ms->cmd[i].args, ms->envp);
		free(pathcmd);
		ms_bad_child_ending(ms->cmd[i].cmd_name);
	}
}

int	ms_exec(t_ms *ms)
{
	int	i;

	ms->pid = malloc(ms->nbcmd * sizeof(int));
	if (!ms->pid)
		return (1);
	if (ms->nbcmd == 1 && ms_isbuiltin(ms->cmd[0].cmd_name))
		return (ms_do_builtin(&ms->cmd[0]));
	i = -1;
	while (++i < ms->nbcmd)
	{
		ms->pid[i] = fork();
		if (!ms->pid[i])
			ms_child(ms, i);
	}
	return (0);
}
