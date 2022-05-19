/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lblanche <lblanche@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 13:16:39 by lblanche          #+#    #+#             */
/*   Updated: 2022/05/03 19:38:46 by tbrissia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <stdio.h>

static t_token	get_redir(char *str, t_token token)
{
	if (ft_strncmp(str, ">", ft_strlen(str)) == 0)
	{
		token.type = REDIR;
		token.value = str;
	}
	else if (ft_strncmp(str, ">>", ft_strlen(str)) == 0)
	{
		token.type = REDIR_APPEND;
		token.value = str;
	}
	else if (ft_strncmp(str, "<", ft_strlen(str)) == 0)
	{
		token.type = INFILE;
		token.value = str;
	}
	else if (ft_strncmp(str, "<<", ft_strlen(str)) == 0)
	{
		token.type = HEREDOC;
		token.value = str;
	}
	return (token);
}

static t_token	get_quote(char *str, t_token token)
{
	if (verify_squote(str))
	{
		token.type = SQUOTE;
		token.value = str;
	}
	if (verify_dquote(str))
	{
		token.type = DQUOTE;
		token.value = str;
	}
	return (token);
}

static t_token	get_token_type(char	*str)
{
	t_token	token;

	token.type = WORD;
	token.value = NULL;
	token = get_redir(str, token);
	token = get_quote(str, token);
	if (ft_strncmp(str, "|", ft_strlen(str)) == 0)
	{
		token.type = PIPE;
		token.value = str;
	}
	else if (ft_strncmp(str, "-", 1) == 0)
	{
		token.type = OPTION;
		token.value = str;
	}
	else if (!(token.value))
	{
		token.type = WORD;
		token.value = str;
	}
	return (token);
}

static int	get_cmd_size(char	**command)
{
	int	i;

	i = 0;
	while (command[i])
		i++;
	return (i);
}

t_token	*tokenize(char	**command)
{
	int		i;
	t_token	*token;

	i = 0;
	token = (t_token *)malloc(sizeof(t_token) * (get_cmd_size(command) + 1));
	if (!token)
		return (NULL);
	while (command[i])
	{
		token[i] = get_token_type(command[i]);
		i++;
	}
	token[i].value = NULL;
	return (token);
}
