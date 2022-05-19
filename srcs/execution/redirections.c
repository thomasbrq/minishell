/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbraquem <tbraquem@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 10:50:29 by tbraquem          #+#    #+#             */
/*   Updated: 2022/05/12 19:14:31 by tbraquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	redirect_to_file(int redir, t_token **token, int i)
{
	int	fd;

	if (redir == REDIR)
	{
		fd = open(token[i + 1]->value, O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (fd < 0)
			return ;
	}
	if (redir == REDIR_APPEND)
	{
		fd = open(token[i + 1]->value, O_CREAT | O_RDWR | O_APPEND, 0644);
		if (fd < 0)
			return ;
	}
	dup2(fd, 1);
	close(fd);
}

void	redirect_in_file(t_token **token, int i)
{
	int	fd;

	fd = open(token[i + 1]->value, O_RDONLY);
	if (fd < 0)
		return ;
	dup2(fd, 0);
	close(fd);
}

void	redirect_heredoc(t_token **token, int i)
{
	char	*line;
	int		fd;

	fd = open("/tmp/.heredoc", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return ;
	while (42)
	{
		line = readline("> ");
		if (ft_strncmp(line, token[i + 1][0].value,
			ft_strlen(token[i + 1][0].value) + ft_strlen(line)) == 0)
			break ;
		ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
	}
	close(fd);
	fd = open("/tmp/.heredoc", O_RDONLY);
	if (fd < 0)
		return ;
	dup2(fd, 0);
	close(fd);
}

int	redirection(t_token **token)
{
	int	i;

	i = 0;
	while (token[i] != NULL && token[i]->type != PIPE)
	{
		if (token[i]->type == REDIR)
			redirect_to_file(REDIR, token, i);
		if (token[i]->type == REDIR_APPEND)
			redirect_to_file(REDIR_APPEND, token, i);
		if (token[i]->type == INFILE)
			redirect_in_file(token, i);
		if (token[i]->type == HEREDOC)
			redirect_heredoc(token, i);
		i++;
	}
	return (0);
}

int	get_lst_len(t_env *env)
{
	int	size;

	size = 0;
	while (env)
	{
		size++;
		env = env->next;
	}
	return (size);
}
