/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export_00.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdjemaa <mdjemaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 11:02:48 by rficht            #+#    #+#             */
/*   Updated: 2023/06/13 01:01:17 by mdjemaa          ###   ########.fr       */
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
 

/**
 * export a new var into ms_env. Carefull, it doesn't free new var.
 * @param exp the new variable to export.
 * @param ms a pointer to minishell.
 * @return 0 if succes 1 if fail. 
 */
int	ms_exp_exportvar(t_export *exp, t_ms *ms)
{
	int	env_varl;

	env_varl = ms_getenv_varl(exp->name, ms);
	if (env_varl >= 0 && !exp->add)
	{
		free(ms->envp[env_varl]);
		ms->envp[env_varl] = ft_strmanyjoin(exp->name, "=", exp->value, 0);
	}
	else
		env_addvar(exp->name, ms);
	return (0);
}

int	exp_split(t_export *exp, char *arg)
{
	int	pos;
	int	flagadd;

	pos = ms_where_is('=', arg);
	flagadd = 0;
	if (pos == -1)
	{
		exp->name = ft_strdup(arg);
		exp->value = 0;
		return (0);
	}
	else if (pos == (int) ft_sstrlen(arg) - 1)
	{
		exp->name = ft_substr(arg, 0, pos);
		exp->value = "";
		return (0);
	}
	else if (arg[pos - 1] == '+')
		flagadd = 1;
	exp->name = ft_substr(arg, 0, pos - flagadd);
	exp->value = ft_substr(arg, pos + 1 , ft_sstrlen(arg) - pos);
	if (!exp->name || !exp->value)
		return (1);
	exp->add = flagadd;
	printf("Name : %s\tValue : %s\tFlag+ : %d\n", exp->name, exp->value, exp->add);
	return (0);
}

void	disp_exp(t_export *exp, int max)
{
	int	n;

	n = -1;
	while (++n < max)
		printf("export %d _ ", n);
		puts(exp[n].name);
		puts(exp[n].value);
		printf("export %d _ \n", exp[n].add);
}

int	ms_exp_init(t_export *exp, char **args)
{
	int	n;

	n = -1;
	while (args[++n])
	{
		if (!valid_name(args[n]))
			return (1);
	}
	n = -1;
	while (args[++n])
	{
		if (exp_split(&exp[n], args[n]))
			return (exp_free(&exp), 1);
	}
	return (0);
}

int	ms_export(t_cmd *cmd)
{
	t_export	*exp;
	int			n;

	if (!cmd || !cmd->args[0])
		return (ft_putstr_fd("msh: export: empty args\n", 2), 1);
	if (!cmd->args[1])
		return (ms_no_arg_export(cmd->ms, cmd->fdout), 0);
	n = 0;
	while (cmd->args[n])
		n++;
	exp = malloc(n * sizeof(exp));
	if (!exp)
		return (1);
	if (ms_exp_init(exp, cmd->args + 1))
		return (exp_free(&exp), 1);
	disp_exp(exp, n);
	// if (ms_exp_exportvar(exp, cmd->ms))
	// 	return (1);
	return (0);
}
