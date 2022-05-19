/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executions_utils_plus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrissia <tbrissia@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 18:27:34 by tbrissia          #+#    #+#             */
/*   Updated: 2022/05/12 18:27:47 by tbrissia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	cutter(t_token **exec_l, int *index, int i, int j)
{
	index[0] = 0;
	index[1] = 0;
	index[2] = j;
	while (exec_l[i][index[2]].type != PIPE && exec_l[i][index[2]].value)
	{
		index[2]++;
		index[0]++;
	}
}
