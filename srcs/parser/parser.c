/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lblanche <lblanche@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 16:32:59 by lblanche          #+#    #+#             */
/*   Updated: 2022/05/12 18:20:18 by tbrissia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	while_cutter(t_token *token, int *index)
{
	while (!is_redirection(token[index[0]]) && token[index[0]].value)
	{
		index[0]++;
		index[2]++;
		if (index[3])
		{
			index[3] = 0;
			return ;
		}
	}
}

static t_token	**malloc_exec_line(t_token *token)
{
	t_token	**exec_line;
	int		i[4];

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	exec_line = (t_token **)malloc(sizeof(t_token *)
			* (get_element_size(token) + 1));
	while (token[i[0]].value)
	{
		i[3] = 0;
		if (is_redirection(token[i[0]]))
		{
			exec_line[i[1]] = (t_token *)malloc(sizeof(t_token) * 2);
			if (is_infile(token[i[0]]))
				i[3] = 1;
			i[1]++;
			i[0]++;
		}
		while_cutter(token, i);
		exec_line[i[1]] = (t_token *)malloc(sizeof(t_token) * (i[2] + 1));
		i[2] = 0;
		i[1]++;
	}
	return (exec_line);
}

void	portal_cutter(t_token *token, int *index, t_token **exec_line)
{
	while (!is_redirection(token[index[2]]) && token[index[2]].value)
	{
		exec_line[index[0]][index[1]] = token[index[2]];
		index[1]++;
		index[2]++;
		if (index[3])
		{
			index[3] = 0;
			break ;
		}
	}
	exec_line[index[0]][index[1]].value = NULL;
	index[1] = 0;
	index[0]++;
}

t_token	**create_execution_line(t_token	*token)
{
	t_token	**exec_line;
	int		index[4];

	index[0] = 0;
	index[1] = 0;
	index[2] = 0;
	exec_line = malloc_exec_line(token);
	if (!exec_line)
		return (NULL);
	while (token[index[2]].value)
	{
		index[3] = 0;
		if (is_redirection(token[index[2]]))
		{
			if (is_infile(token[index[0]]))
				index[3] = 1;
			exec_line[index[0]][index[1]] = token[index[2]];
			exec_line[index[0]][index[1] + 1].value = NULL;
			index[0]++;
			index[2]++;
		}
		portal_cutter(token, index, exec_line);
	}
	exec_line[index[0]] = NULL;
	return (exec_line);
}
