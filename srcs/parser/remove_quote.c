/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrissia <tbrissia@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 18:24:31 by tbrissia          #+#    #+#             */
/*   Updated: 2022/05/10 11:56:19 by tbraquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*kill_quote(char *old_str)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 1;
	str = old_str + 1;
	while (i < (int)ft_strlen(old_str) - 2)
	{
		str[i] = old_str[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}

t_token	*remove_quote(t_token *token)
{
	int		i;
	char	*str;

	i = 0;
	while (token[i].value)
	{
		if (token[i].type != SQUOTE && token[i].type != DQUOTE)
			i++;
		else
		{
			str = kill_quote(token[i].value);
			token[i].value = str;
			i++;
		}
	}
	return (token);
}
