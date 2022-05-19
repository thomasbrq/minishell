/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lblanche <lblanche@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 16:38:20 by lblanche          #+#    #+#             */
/*   Updated: 2022/05/04 09:55:30 by tbrissia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	no_quote(char *set, char c)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

int	is_in_charset(const char *s, int index, char c, char *set)
{
	int	double_quote;
	int	simple_quote;

	double_quote = 0;
	simple_quote = 0;
	between_quote_check(&simple_quote, &double_quote, index, s);
	if (c == '\"' && (!(simple_quote % 2)))
	{
		if (double_quote % 2)
			return (2);
		else
			return (1);
	}
	if (c == '\'' && (!(double_quote % 2)))
	{
		if (simple_quote % 2)
			return (2);
		else
			return (1);
	}
	if ((!(double_quote % 2)) && (!(simple_quote % 2)))
		if (no_quote(set, c))
			return (1);
	return (0);
}

void	between_quote_check(int *s_quote, int *d_quote, int i, const char *s)
{
	int	counter;

	counter = 0;
	while (counter < i)
	{
		if (s[counter] == '\'' && (!(*d_quote % 2)))
			(*s_quote)++;
		else if (s[counter] == '\"' && (!(*s_quote % 2)))
			(*d_quote)++;
		counter ++;
	}
}

char	*array_alloc_fill(char *ret, size_t let, char const *s, size_t i)
{
	ret = array_alloc(ret, let);
	ret = array_fill(ret, let - 1, s, i);
	return (ret);
}
