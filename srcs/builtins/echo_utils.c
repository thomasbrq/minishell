/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrissia <tbrissia@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 14:25:09 by tbrissia          #+#    #+#             */
/*   Updated: 2022/05/12 18:08:52 by tbraquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	space_echo(int *extra, t_token *cmd, t_mini *shell, int *save)
{
	if (compare_strings(cmd[extra[1]].value, "$?"))
	{
		printf("%d", shell->last_status);
		(*save) += 2;
	}
	else
	{
		printf("%s", cmd[extra[1]].value);
		if (cmd[extra[1]].type != SQUOTE && cmd[extra[1]].type != DQUOTE)
			(*save) += ft_strlen(cmd[extra[1]].value);
		else
			(*save) += (ft_strlen(cmd[extra[1]].value) + 2);
	}
}
