/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbraquem <tbraquem@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 16:16:56 by tbraquem          #+#    #+#             */
/*   Updated: 2022/05/12 18:32:49 by tbrissia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	compare_strings(char *command, char *received)
{
	if (!command || !received)
		return (0);
	if (ft_strncmp(command, received, ft_strlen(command)
			+ ft_strlen(received)) == 0)
		return (1);
	return (0);
}

static	int	count_args(t_token *command)
{
	int	i;

	i = 0;
	while (command[i].value)
		i++;
	return (i);
}

int	is_builtins_nofork(t_token *command, t_mini *shell)
{
	shell->argc = count_args(command);
	if (compare_strings("unset", command[0].value))
	{
		shell->last_status = cmd_unset(&(shell->env), command[1].value);
		return (1);
	}
	if (compare_strings("export", command[0].value))
	{
		shell->last_status = cmd_export(shell->argc, &(shell->env),
				command[1].value);
		return (1);
	}
	if (compare_strings("cd", command[0].value))
	{
		shell->last_status = cmd_cd(shell->env, command[1].value);
		return (1);
	}
	if (compare_strings("exit", command[0].value))
		cmd_exit(shell);
	return (0);
}

int	is_buil_infork(char **command, t_mini *shell, char *line, t_token *cmd)
{
	if (compare_strings("env", command[0]))
	{
		shell->last_status = cmd_env(shell->env);
		return (1);
	}
	if (compare_strings("pwd", command[0]))
	{
		shell->last_status = cmd_pwd();
		return (1);
	}
	if (compare_strings("echo", command[0]))
	{
		cmd_echo(cmd, shell, line);
		return (1);
	}
	return (0);
}
