/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lblanche <lblanche@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 17:44:42 by lblanche          #+#    #+#             */
/*   Updated: 2022/04/27 12:52:36 by tbraquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	is_redirection(t_token token)
{
	if (token.type == REDIR
		|| token.type == REDIR_APPEND || token.type == INFILE
		|| token.type == HEREDOC)
		return (1);
	if (token.type == PIPE)
		return (2);
	else
		return (0);
}

int	is_infile(t_token token)
{
	if (token.type == INFILE || token.type == HEREDOC)
		return (1);
	return (0);
}

static int	count_redirections(t_token *token)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	while (token[i].value)
	{
		if (is_redirection(token[i]))
			nb++;
		i++;
	}
	return (nb);
}

/*
	Get the number of elements in the line.
	(ls -la | grep main) = 3;
	(ls -la) = 1; (|) = 1; (grep main) = 1;
*/

int	get_element_size(t_token *token)
{
	int	size;

	size = (count_redirections(token) * 2) + 1;
	if (is_redirection(token[0]) == 1)
		size--;
	return (size);
}
