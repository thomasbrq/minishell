/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbraquem <tbraquem@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 12:57:10 by tbraquem          #+#    #+#             */
/*   Updated: 2022/04/30 14:04:43 by tbraquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	env_push(t_env **begin, char *data)
{
	t_env	*temp;
	t_env	*new;

	if (!*begin)
	{
		*begin = (t_env *) malloc(sizeof(t_env *));
		if (!*begin)
			return ;
		(*begin)->data = data;
		(*begin)->next = NULL;
		return ;
	}
	temp = *begin;
	while ((*begin)->next)
		*begin = (*begin)->next;
	new = (t_env *) malloc(sizeof(t_env *));
	if (!*begin)
		return ;
	new->data = data;
	new->next = NULL;
	(*begin)->next = new;
	*begin = temp;
}

void	env_free(t_env **begin)
{
	t_env	*temp;

	temp = NULL;
	while (*begin)
	{
		temp = (*begin)->next;
		free(*begin);
		*begin = temp;
	}
	*begin = NULL;
}

void	env_print(t_env *begin)
{
	while (begin)
	{
		printf("%s\n", begin->data);
		begin = begin->next;
	}
}

t_env	*get_envp(t_env *env, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		env_push(&env, envp[i]);
		i++;
	}
	return (env);
}
