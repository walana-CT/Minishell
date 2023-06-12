/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export_00.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdjemaa <mdjemaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 11:02:48 by rficht            #+#    #+#             */
/*   Updated: 2023/06/12 18:30:34 by mdjemaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_addvar(char *new_var, t_ms *ms)
{
	char	**new_envp;
	int		n;

	n = -1;
	new_envp = calloc(ms_sizeof_tab(ms->envp) + 2, sizeof(char *));
	if (!new_envp)
		ms_crash(ms);
	while (ms->envp[++n])
		new_envp[n] = ms->envp[n];
	new_envp[n] = strdup(new_var);
	free(ms->envp);
	ms->envp = new_envp;
}

int	valid_name(char *new_var)
{
	if (*new_var == '=' || *new_var == '+')
		return (FALSE);
	while (*new_var && *new_var != '=')
	{
		if (*new_var == '+')
		{
			if (*(new_var + 1) == '=')
				return (TRUE);
			return (FALSE);
		}
		if (!ft_isalnum(*new_var) && *new_var != '_')
			return (FALSE);
		new_var++;
	}
	return (TRUE);
}

void	exp_free(t_export **exp)
{
	int	n;

	n = -1;
	while (exp[++n])
	{
		if (exp[n]->name)
			ft_freestr(&exp[n]->name);
		if (exp[n]->value)
			ft_freestr(&exp[n]->value);
		ft_freenull((void **) &exp[n]);
	}
	free(exp);
}

/**
 * export a new var into ms_env. Carefull, it doesn't free new var.
 * @param new_var the new variable to export.
 * @param ms a pointer to minishell.
 * @return 0 if succes 1 if fail. 
 */
int	ms_exportvar(char *new_var, t_ms *ms)
{
	int	env_varl;

	if (!valid_name(new_var))
	{
		ft_putstr_fd("msh: export: not a valid identifier\n", 2);
		return (1);
	}
	env_varl = ms_getenv_varl(new_var, ms);
	if (env_varl >= 0)
	{
		free(ms->envp[env_varl]);
		ms->envp[env_varl] = ft_strdup(new_var);
	}
	else
		env_addvar(new_var, ms);
	return (0);
}

int	exp_split(t_export *exp, char *arg)
{
	int	pos;

	pos = ms_where_is('=', arg);
	if (arg[pos - 1] == '+')
	{
		pos--;
		exp->add = 1;
	}
	exp->name = ft_substr(arg, 0, pos);
	exp->value = ft_substr(arg, pos + 1 + exp->add, ft_sstrlen(arg) - (pos + 1 + exp->add));
	printf("SPLIT %s %s %d\n", exp->name, exp->value, exp->add);
	if (!exp->name || !exp->value)
		return (1);
	return (0);
}

void	disp_exp(t_export **exp)
{
	int	n;

	n = -1;
	while (exp[++n])
		printf("export %d _ Name : %s Value : %s Flag+ : %d\n", n, exp[n]->name, exp[n]->value, exp[n]->add);
}

int	ms_exp_init(t_export **exp, char **args)
{
	int	n;

	n = -1;
	while (args[++n])
	{
		if (!valid_name(args[n]))
			return (1);
		exp[n] = malloc(sizeof(exp));
		exp[n]->name = 0;
		exp[n]->value = 0;
		exp[n]->add = 0;
	}
	disp_exp(exp);
	n = -1;
	while (args[++n])
	{
		if (exp_split(exp[n], args[n]))
			return (exp_free(exp), 1);
	}
	disp_exp(exp);
	return (0);
}

int	ms_export(t_cmd *cmd)
{
	t_export	**exp;
	int			n;

	if (!cmd || !cmd->args[0])
		return (ft_putstr_fd("msh: export: empty args\n", 2), 1);
	if (!cmd->args[1])
		return (ms_no_arg_export(cmd->ms, cmd->fdout), 0);
	n = 0;
	while (cmd->args[n])
		n++;
	exp = ft_calloc(n, sizeof(*exp));
	if (!exp)
		return (1);
	if (ms_exp_init(exp, cmd->args + 1))
		return (exp_free(exp), 1);
/*	if (ms_exportvar(exp, cmd->ms))
		return (1);*/
	return (0);
}
