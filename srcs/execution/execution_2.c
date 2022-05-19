/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbraquem <tbraquem@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 11:06:33 by tbraquem          #+#    #+#             */
/*   Updated: 2022/05/12 19:32:34 by tbraquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	execution_2(t_token **execl, t_mini *shell, char **fcmd, char *line)
{
	char	**envp;

	envp = list_to_tab(shell->env);
	signal(SIGINT, &kill_process);
	redirection(execl);
	shell->cmd = get_cmd(shell->path_arr, fcmd[0]);
	if (!is_buil_infork(fcmd, shell, line, execl[0]))
	{
		shell->last_status = execve(shell->cmd, fcmd, envp);
		if (shell->last_status < 0)
			print_cmd_error(fcmd[0]);
	}
	envp = free_2d(envp);
}

int	checker_execution(t_token **exec_l, int *i, t_mini *shell)
{
	if (exec_l[*i] == NULL)
		return (1);
	if (exec_l[*i]->type == PIPE)
		(*i)++;
	if (is_builtins_nofork(exec_l[*i], shell))
		return (1);
	if (compare_strings(exec_l[*i]->value, "$?"))
	{
		free(exec_l[*i]->value);
		exec_l[*i]->value = ft_itoa(shell->last_status);
	}
	return (0);
}

void	dup_fd(int *infos, t_token **exec_l, int *i, int *fd)
{
	dup2(infos[1], 0);
	if (infos[2])
	{
		redirection(exec_l);
		(*i) += 2;
	}
	if (exec_l[*i + 1] != NULL && !is_token_redirection(exec_l[*i])
		&& !is_token_redirection(exec_l[*i + 1]))
		dup2(fd[1], 1);
	close(fd[0]);
}

void	wait_child(int *infos, t_mini *shell, int *fd, int *i)
{
	waitpid(infos[0], &shell->last_status, 0);
	close(fd[1]);
	if (infos[2])
		(*i) += 2;
	infos[1] = fd[0];
	(*i)++;
}

char	**list_to_tab(t_env	*env)
{
	char	**envp;
	int		i;

	i = 0;
	envp = malloc(sizeof(char *) * (get_lst_len(env) + 1));
	if (!envp)
		return (NULL);
	while (env)
	{
		envp[i++] = ft_strdup(env->data);
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}
