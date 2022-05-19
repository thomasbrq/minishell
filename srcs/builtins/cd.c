/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrissia <tbrissia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 14:42:21 by tbrissia          #+#    #+#             */
/*   Updated: 2022/05/11 18:26:50 by lblanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static void	modif_env(t_env *env, char *path)
{
	char	*copy_pwd;
	char	*new_pwd;
	t_env	*begin;

	begin = env;
	while (ft_strncmp(env->data, "PWD=", 4))
		env = env->next;
	copy_pwd = ft_strdup(env->data);
	new_pwd = ft_strjoin("PWD=", path);
	env->data = new_pwd;
	env = begin;
	while (ft_strncmp(env->data, "OLDPWD=", 7))
		env = env->next;
	new_pwd = ft_strjoin("OLD", copy_pwd);
	env->data = new_pwd;
	env = begin;
}

static char	*get_pwd(void)
{
	int		error;
	int		i;
	char	*buff;

	error = 0;
	i = 1;
	while (error == 0)
	{
		buff = (char *)malloc(sizeof(char) * i);
		if (getcwd(buff, i))
			error = 1;
		else
		{
			i++;
			free(buff);
		}
	}
	return (buff);
}

static char	*get_home(t_env *env)
{
	t_env	*begin;
	char	*path;

	begin = env;
	while (ft_strncmp(env->data, "HOME=", 5))
		env = env->next;
	path = ft_strdup((env->data) + 5);
	env = begin;
	return (path);
}

int	cmd_cd(t_env *env, char *path)
{
	char	*new_path;

	if (!path)
		path = get_home(env);
	if (chdir(path))
	{
		print_error();
		return (-1);
	}
	else
	{
		new_path = get_pwd();
		modif_env(env, new_path);
		return (0);
	}
}
