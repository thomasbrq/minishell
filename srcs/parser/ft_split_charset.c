/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_charset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbraquem <tbraquem@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 10:01:41 by tbraquem          #+#    #+#             */
/*   Updated: 2022/05/04 09:56:16 by tbrissia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

size_t	count_word(char const *s, char *set)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	if (!s[i])
		return (0);
	if (!is_in_charset(s, i, s[i], set))
			count++;
	while (s[i])
	{
		if (is_in_charset(s, i, s[i], set))
		{
			if (!(is_in_charset(s, i + 1, s[i + 1], set)))
				count++;
		}
		else if ((!s[i + 1]) && !is_in_charset(s, i, s[i], set))
			count++;
		i++;
	}
	return (count - 1);
}

char	*array_alloc(char *array, size_t nl)
{
	array = (char *) malloc((nl) * sizeof(char));
	if (!array)
		return (NULL);
	return (array);
}

char	*array_fill(char *array, size_t nl, char const *o, size_t idx)
{
	size_t	i;

	i = 0;
	while (i < (nl))
	{
		array[i] = o[idx];
		i++;
		idx++;
	}
	array[i] = '\0';
	return (array);
}

void	count_letters(char const *s, char **ret, size_t wordc, char *set)
{
	size_t	let;
	size_t	nbr;
	size_t	i;

	let = 0;
	nbr = 0;
	i = 0;
	while (nbr < wordc)
	{
		let = 0;
		while (s[i] && is_in_charset(s, i, s[i], set))
			i++;
		while (s[i] && !is_in_charset(s, i, s[i], set))
		{
			let++;
			i++;
		}
		if (is_in_charset(s, i, s[i], set) == 2)
			ret[nbr] = array_alloc_fill(ret[nbr], let + 3, s, (i - let - 1));
		else
			ret[nbr] = array_alloc_fill(ret[nbr], let + 1, s, i - let);
		nbr++;
	}
}

char	**ft_split_charset(char const *s, char *set)
{
	char	**ret;
	size_t	wordc;
	size_t	nbr;
	size_t	i;

	if (!s)
		return (NULL);
	wordc = count_word(s, set);
	nbr = 0;
	i = 0;
	ret = (char **) malloc((wordc + 1) * sizeof(char *));
	if (!ret)
		return (NULL);
	ret[wordc] = NULL;
	count_letters(s, ret, wordc, set);
	return (ret);
}
