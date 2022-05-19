/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbraquem <tbraquem@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 12:54:55 by tbraquem          #+#    #+#             */
/*   Updated: 2022/05/09 15:25:05 by tbraquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	cmd_exit(t_mini *shell)
{
	env_free(&shell->env);
	exit(shell->last_status);
}
