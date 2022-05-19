/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrissia <tbrissia@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 09:32:06 by tbrissia          #+#    #+#             */
/*   Updated: 2022/05/12 18:20:04 by tbrissia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	initialise_me(int *index)
{
	int	i;

	i = 0;
	while (i < 5)
		index[i++] = 0;
}

int	verif_error(int *index)
{
	if (index[2] % 2 || index[1] % 2)
	{
		print_error();
		return (-1);
	}
	return (0);
}

int	line_checker(char *line, t_mini *shell)
{
	int	index[5];

	initialise_me(index);
	while (line[index[0]])
	{
		if (line[index[0]] == '-' && line[index[0] + 1] == 'n')
			index[3] = 1;
		if (line[index[0]] == '\\' || line[index[0]] == ';')
		{
			print_error();
			return (-1);
		}
		if (line[index[0]] == '\'' && !(index[2] % 2))
			index[1]++;
		if (line[index[0]] == '\"' && !(index[1] % 2))
			index[2]++;
		index[0]++;
		if (line[index[0]] == ' ')
			index[4]++;
	}
	if (verif_error(index) == -1)
		return (-1);
	index[4] = (index[4] - 1) - index[3];
	shell->space_line = index[4];
	return (0);
}
