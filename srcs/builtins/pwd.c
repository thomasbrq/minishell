/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbraquem <tbraquem@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 12:55:32 by tbraquem          #+#    #+#             */
/*   Updated: 2022/05/06 14:36:01 by tbrissia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <errno.h>

int	cmd_pwd(void)
{
	char	*buffer;
	char	*ret;
	int		i;

	i = 1;
	ret = NULL;
	while (ret == NULL)
	{
		buffer = (char *)malloc((i) * sizeof(char));
		if (!buffer)
			return (-1);
		ret = getcwd(buffer, i);
		if (ret == NULL)
			free(buffer);
		if (ret == NULL && (errno == 13 || errno == 2))
		{
			print_error();
			return (-1);
		}
		i++;
	}
	printf("%s\n", ret);
	free(buffer);
	return (0);
}
