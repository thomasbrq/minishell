/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbraquem <tbraquem@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 10:18:14 by tbraquem          #+#    #+#             */
/*   Updated: 2022/04/12 14:25:43 by tbraquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <stdio.h>

char	*get_next_line(int fd)
{
	static int	nbr;
	static char	buff[BUFFER_SIZE / BUFFER_SIZE + 1];
	char		*result;

	result = NULL;
	if (nbr == 0)
	{
		nbr = read(fd, buff, 1);
		buff[nbr] = '\0';
	}
	if (nbr > 0 && buff[0] != '\0')
		result = ft_sread(fd, buff, result, nbr);
	else
		return (NULL);
	return (result);
}

char	*ft_sread(int fd, char *buff, char *result, int nbr)
{
	while (nbr > 0 && ft_sstrchr(result, '\n'))
	{
		result = ft_sstrjoin(result, buff);
		nbr = read(fd, buff, 1);
		buff[nbr] = '\0';
	}
	return (result);
}
