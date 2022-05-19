/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbraquem <tbraquem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 10:05:28 by tbraquem          #+#    #+#             */
/*   Updated: 2022/05/11 15:12:11 by lblanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "utils.h"

void	signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	init(t_mini *shell, char **envp)
{
	welcome_message();
	shell->env = NULL;
	shell->last_status = 0;
	shell->env = get_envp(shell->env, envp);
	shell->path = get_path(list_to_tab(shell->env));
	shell->path_arr = ft_split(shell->path, ':');
}

int	core(char *line, t_mini *shell)
{
	char		**command;
	t_token		*token;
	t_token		**exec_line;

	if (line_checker(line, shell) < 0)
		return (-1);
	command = ft_split_charset(line, " \t");
	command = remplace_env(command, shell->env);
	token = tokenize(command);
	token = remove_quote(token);
	add_history(line);
	exec_line = create_execution_line(token);
	free(token);
	run_pipeline(shell, exec_line, line);
	free_all(&command, &line, &exec_line);
	return (0);
}

void	readline_loop(t_mini *shell)
{
	char		*line;

	while (42)
	{
		line = readline("\033[1;35mminishell > \033[0;37m");
		if (line)
			core(line, shell);
		else
		{
			free(line);
			exit(0);
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_mini			shell;

	(void) argc;
	(void) argv;
	init(&shell, envp);
	signal(SIGINT, &signal_handler);
	signal(SIGQUIT, SIG_IGN);
	readline_loop(&shell);
	return (0);
}
