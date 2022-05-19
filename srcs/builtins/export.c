/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbraquem <tbraquem@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 12:55:10 by tbraquem          #+#    #+#             */
/*   Updated: 2022/05/12 18:14:48 by tbraquem         ###   ########.fr       */
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

static void	modify_env(t_env **env, char **line, char *l)
{
	char	*temp;

	if (!line[1] && (ft_strchr(l, '=') == NULL))
		return ;
	if (!line[1])
	{
		(*env)->data = ft_strjoin(line[0], "=");
		return ;
	}
	temp = ft_strjoin(line[0], "=");
	(*env)->data = ft_strjoin(temp, line[1]);
	free(temp);
}

static void	add_env(t_env **env, char **line, char *l)
{
	char	*temp;
	char	*temp2;

	if (!line[1] && (ft_strchr(l, '=') == NULL))
		return ;
	if (!line[1])
	{
		temp = ft_strjoin(line[0], "=");
		env_push(env, temp);
		return ;
	}
	temp2 = ft_strjoin(line[0], "=");
	temp = ft_strjoin(temp2, line[1]);
	env_push(env, temp);
	free(temp2);
}

static void	set_env(t_env *env, char *line)
{
	char	**array_line;
	char	**temp;
	t_env	*begin;

	if (checker_line(line))
		return ;
	array_line = ft_split(line, '=');
	begin = env;
	while (env)
	{
		temp = ft_split(env->data, '=');
		if (ft_strncmp(array_line[0], temp[0], (len_equal(temp[0]))
				+ len_equal(array_line[0])) == 0)
		{
			modify_env(&env, array_line, line);
			temp = free_2d(temp);
			array_line = free_2d(array_line);
			return ;
		}
		temp = free_2d(temp);
		env = env->next;
	}
	add_env(&begin, array_line, line);
	array_line = free_2d(array_line);
}

int	cmd_export(int argc, t_env **env, char *line)
{
	if (argc == 1)
	{
		env_print(*env);
		return (0);
	}
	else if (argc == 2)
	{
		set_env(*env, line);
		return (0);
	}
	else
	{
		print_error();
		return (-1);
	}
}
