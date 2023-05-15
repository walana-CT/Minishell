/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rficht <robin.ficht@free.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 20:28:47 by mdjemaa           #+#    #+#             */
/*   Updated: 2023/05/15 15:45:46 by rficht           ###   ########.fr       */
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

void	ms_printcmd(t_cmd cmd)
{
	printf(YELLOW"commande %d\n"RESET, cmd.nb);
	ft_printstrtab(cmd.args, "ARGS");
	printf("PATH : %s\n", cmd.path);
	printf("Filein : %s \t fdin %d\n", cmd.filein, cmd.fdin);
	printf("Fileout : %s \t fdout %d\n", cmd.fileout, cmd.fdout);
	printf("Pipein %d \t Pipeout %d\n", cmd.ms->pipe[cmd.nb][0], \
		cmd.ms->pipe[cmd.nb][1]);
}

void	ms_exec(t_ms *ms)
{
	int	i;

	i = -1;
	while (++i < ms->nbcmd)
	{
		if (ms_isbuiltin(ms->cmd[i].cmd_name))
			ms_do_builtin(&ms->cmd[i]);
		else
			ms_printcmd(ms->cmd[i]);
	}
}
