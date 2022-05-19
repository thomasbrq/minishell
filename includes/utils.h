/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbraquem <tbraquem@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 11:06:33 by tbraquem          #+#    #+#             */
/*   Updated: 2022/05/12 19:18:57 by tbraquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include "get_next_line.h"
# include "lexer.h"
# include "pipex.h"
# include "../libft/libft.h"

typedef struct s_env
{
	char			*data;
	struct s_env	*next;
}				t_env;

typedef struct s_mini
{
	char		*path;
	char		*cmd;
	char		**path_arr;
	int			pid;
	int			argc;
	int			last_status;
	t_env		*env;
	int			space_line;
}				t_mini;

// Checker
int		line_checker(char *line, t_mini *shell);

// Lexer
t_token	*tokenize(char	**command);
int		verify_dquote(char *str);
int		verify_squote(char *str);

// Parser
t_token	**create_execution_line(t_token	*token);
char	**remplace_env(char **command, t_env *env);

// Parser utils
int		is_redirection(t_token token);
int		is_infile(t_token token);
int		get_element_size(t_token *token);

// Split charset
char	**ft_split_charset(const char	*s, char *set);
int		is_in_charset(const char *s, int index, char c, char *set);
void	between_quote_check(int *s_quote, int *d_quote, int i, const char *s);
char	*array_alloc_fill(char *ret, size_t let, char const *s, size_t i);
char	*array_alloc(char *array, size_t nl);
char	*array_fill(char *array, size_t nl, char const *o, size_t idx);

// Execution
int		redirection(t_token **token);
int		cmd(t_token **exec_l, int i, t_mini *shell, char *line);
void	exec_cmd(t_mini *shell, t_token **exec_l, char **full_cmd, char *line);
void	run_pipeline(t_mini *shell, t_token **exec_l, char *line);
int		get_lst_len(t_env *env);
char	**list_to_tab(t_env	*env);
void	wait_child(int *infos, t_mini *shell, int *fd, int *i);
void	dup_fd(int *infos, t_token **exec_l, int *i, int *fd);
int		checker_execution(t_token **exec_l, int *i, t_mini *shell);
void	execution_2(t_token **execl, t_mini *shell, char **fcmd, char *line);

// Execution utils
char	**get_full_command(t_token **exec_l, int j, int i);
void	cutter(t_token **exec_l, int *index, int i, int j);
int		is_token_redirection(t_token *token);
int		is_token_out(t_token *token);
int		is_token_in(t_token *token);
int		redirection_handler(t_token	**exec_l, int *i);
t_token	*remove_quote(t_token *token);
void	kill_process(int status);

// Redirections
void	redirect_to_file(int redir, t_token **token, int i);
void	redirect_in_file(t_token **token, int i);
void	redirect_heredoc(t_token **token, int i);

// Envp
char	**list_to_tab(t_env	*env);
t_env	*get_envp(t_env *env, char **envp);
void	env_push(t_env **begin, char *data);
void	env_free(t_env **begin);
void	env_print(t_env *begin);

// Builtins functions.
int		cmd_env(t_env *begin);
int		cmd_pwd(void);
int		cmd_export(int argc, t_env **env, char *line);
void	cmd_exit(t_mini *shell);
int		cmd_unset(t_env **env, char *line);
int		cmd_cd(t_env *env, char *path);
void	cmd_echo(t_token *command, t_mini *shell, char *line);

// Builtins Utils
int		is_builtins_nofork(t_token *command, t_mini *shell);
int		is_buil_infork(char **command, t_mini *shell, char *line, t_token *cmd);
int		compare_strings(char *command, char *received);
int		checker_line(char *line);
void	space_echo(int *extra, t_token *cmd, t_mini *shell, int *save);

// Free
char	**free_2d(char **array);
void	free_all(char ***command, char **line, t_token ***exec_l);

// Error
void	print_cmd_error(char *s);
void	print_error(void);

// Welcome
void	welcome_message(void);

#endif
