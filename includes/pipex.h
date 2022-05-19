/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lblanche <lblanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 15:27:21 by lblanche          #+#    #+#             */
/*   Updated: 2022/04/19 14:34:11 by lblanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>

typedef struct s_pipex
{
	int		fd[2];
	int		input;
	int		output;
	int		pid1;
	int		pid2;
	char	**cmd_args;
	char	*cmd;
	char	*paths;
	char	**path_arr;
}	t_pipex;

void	first_child(t_pipex pipex, char **argv, char **envp);
void	second_child(t_pipex pipex, char **argv, char **envp);
void	parent_free(t_pipex *pipex);
void	child_free(t_pipex *pipex);
int		pipex_func(int argc, char **argv, char **envp);
char	*get_cmd(char **paths, char *cmd);
char	*get_path(char **envp);

#endif
