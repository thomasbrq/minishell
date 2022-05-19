/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbraquem <tbraquem@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 12:55:49 by tbraquem          #+#    #+#             */
/*   Updated: 2022/05/06 14:29:49 by tbrissia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static int	len_equal(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '=')
		i++;
	return (i);
}

t_env	**check_env(t_env **env, char *line)
{
	char	**temp;
	t_env	*previous;
	t_env	*begin;

	previous = NULL;
	begin = *env;
	while (*env)
	{
		temp = ft_split((*env)->data, '=');
		if (ft_strncmp(line, temp[0], (len_equal(temp[0]))
				+ len_equal(line)) == 0)
		{
			if (previous != NULL)
				previous->next = (*env)->next;
			free(*env);
			temp = free_2d(temp);
			*env = previous;
			return (env);
		}
		temp = free_2d(temp);
		previous = *env;
		*env = (*env)->next;
	}
	*env = begin;
	return (env);
}

int	cmd_unset(t_env **env, char *line)
{
	t_env	*begin;
	int		i;

	i = 0;
	if (!line)
		return (-1);
	begin = *env;
	while (line[i])
	{
		if (line[i++] == '=')
		{
			print_error();
			return (-1);
		}
	}
	env = check_env(env, line);
	if (*env)
		*env = begin;
	else
	{
		free(*env);
		*env = begin->next;
	}
	return (0);
}
