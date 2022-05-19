/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbraquem <tbraquem@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 15:06:05 by tbraquem          #+#    #+#             */
/*   Updated: 2022/05/11 17:15:43 by tbraquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static char	*get_env(char *command, char **temp_command, t_env *env)
{
	char	**temp_env;
	t_env	*begin;

	begin = env;
	command = ft_strdup("                                                   ");
	while (env)
	{
		temp_env = ft_split(env->data, '=');
		if (compare_strings(temp_env[0], temp_command[0]))
		{
			free(command);
			command = ft_strdup(temp_env[1]);
		}
		temp_env = free_2d(temp_env);
		env = env->next;
	}
	env = begin;
	return (command);
}

static char	*get_command(char **temp_command, t_env *env, char **command, int i)
{
	char	**split;

	if (temp_command[1])
	{
		split = ft_split(temp_command[1], '\"');
		command[i] = get_env(command[i], split, env);
		split = free_2d(split);
	}
	else
		command[i] = get_env(command[i], temp_command, env);
	return (command[i]);
}

char	**remplace_env(char **command, t_env *env)
{
	int		i;
	char	**temp_command;

	i = 0;
	while (command[i])
	{
		if (command[i][0] == '$' && command[i][1] == '?')
			return (command);
		if (command[i][0] == '$' || (command[i][0] == '\"'
								&& command[i][1] == '$'))
		{
			temp_command = ft_split(command[i], '$');
			if (!temp_command[0])
				return (command);
			free(command[i]);
			command[i] = get_command(temp_command, env, command, i);
			temp_command = free_2d(temp_command);
		}
		i++;
	}
	return (command);
}
