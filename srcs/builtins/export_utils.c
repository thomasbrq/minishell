/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbraquem <tbraquem@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 12:55:10 by tbraquem          #+#    #+#             */
/*   Updated: 2022/05/12 18:15:24 by tbraquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	checker_line(char *line)
{
	if (!*line || *line == '=')
	{
		print_error();
		return (1);
	}
	return (0);
}
