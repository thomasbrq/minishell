/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbraquem <tbraquem@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 10:18:11 by tbraquem          #+#    #+#             */
/*   Updated: 2022/04/12 11:39:00 by tbraquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>
# define BUFFER_SIZE 100

char	*ft_sstrjoin(char *s1, char *s2);
size_t	ft_sstrlen(const char *s);
int		ft_sstrchr(char *str, int c);
char	*ft_sread( int fd, char *buff, char *str, int res);
char	*get_next_line(int fd);
#endif
