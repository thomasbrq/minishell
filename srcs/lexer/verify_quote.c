/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrissia <tbrissia@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 17:31:16 by tbrissia          #+#    #+#             */
/*   Updated: 2022/05/03 17:35:14 by tbrissia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	verify_squote(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '\'')
	{
		while (str[i])
			i++;
		if (str[i - 1] == '\'')
			return (1);
	}
	return (0);
}

int	verify_dquote(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '\"')
	{
		while (str[i])
			i++;
		if (str[i - 1] == '\"')
			return (1);
	}
	return (0);
}
