/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbraquem <tbraquem@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 10:49:07 by tbraquem          #+#    #+#             */
/*   Updated: 2022/05/12 19:19:04 by tbraquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	kill_process(int status)
{
	(void) status;
	exit(1);
}

void	exec_cmd(t_mini *shell, t_token **exec_l, char **full_cmd, char *line)
{
	int		pid;
	char	**envp;
	int		status ;

	status = 0;
	envp = list_to_tab(shell->env);
	shell->path = get_path(list_to_tab(shell->env));
	free_2d(shell->path_arr);
	shell->path_arr = ft_split(shell->path, ':');
	pid = fork();
	if (pid == -1)
		exit(1);
	else if (pid == 0)
	{
		execution_2(exec_l, shell, full_cmd, line);
		free(shell->cmd);
		exit(1);
	}
	else
		waitpid(pid, &status, 0);
	free_2d(envp);
	exit(status);
}

int	cmd(t_token **exec_l, int i, t_mini *shell, char *line)
{
	char	**full_command;

	full_command = get_full_command(exec_l, 0, i);
	signal(SIGINT, &kill_process);
	exec_cmd(shell, &exec_l[i], full_command, line);
	exit (1);
}

void	run_pipeline(t_mini *shell, t_token **exec_l, char *line)
{
	int	fd[2];
	int	i;
	int	infos[3];

	i = 0;
	infos[1] = 0;
	while (exec_l[i])
	{
		infos[2] = redirection_handler(exec_l, &i);
		if (checker_execution(exec_l, &i, shell))
			break ;
		pipe(fd);
		infos[0] = fork();
		if (infos[0] == -1)
			exit(1);
		else if (infos[0] == 0)
		{
			dup_fd(infos, exec_l, &i, fd);
			cmd(exec_l, i, shell, line);
		}
		else
			wait_child(infos, shell, fd, &i);
	}
}
