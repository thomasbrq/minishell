/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbraquem <tbraquem@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 10:51:23 by tbraquem          #+#    #+#             */
/*   Updated: 2022/05/12 18:27:52 by tbrissia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	**get_full_command(t_token **el, int j, int i)
{
	char	**result;
	int		index[3];

	cutter(el, index, i, j);
	result = (char **)malloc(sizeof(char *) * (index[0] + 1));
	if (!result)
		exit(1);
	index[2] = 0;
	while ((el[i][j].type == OPTION || el[i][j].type == WORD ||
					el[i][j].type == DQUOTE || el[i][j].type == SQUOTE) &&
					index[2] < index[0])
	{
		result[index[1]] = (char *)malloc(sizeof(char)
				* (ft_strlen(el[i][j].value) + 1));
		result[index[1]] = el[i][j].value;
		j++;
		index[1]++;
		index[2]++;
	}
	result[index[1]] = NULL;
	return (result);
}

int	is_token_redirection(t_token *token)
{
	if (!token)
		return (0);
	if (token->type == REDIR || token->type == REDIR_APPEND
		|| token->type == INFILE || token->type == HEREDOC)
		return (1);
	return (0);
}

int	is_token_out(t_token *token)
{
	if (!token)
		return (0);
	if (token->type == REDIR || token->type == REDIR_APPEND)
		return (1);
	return (0);
}

int	is_token_in(t_token *token)
{
	if (!token)
		return (0);
	if (token->type == INFILE || token->type == HEREDOC)
		return (1);
	return (0);
}

int	redirection_handler(t_token	**exec_l, int *i)
{
	int	redir;

	redir = 0;
	while (is_token_out(exec_l[*i]) && exec_l[*i])
		(*i) = (*i) + 2;
	if (is_token_in(exec_l[*i]))
		redir = 1;
	return (redir);
}
