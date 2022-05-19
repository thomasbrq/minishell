/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrissia <tbrissia@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 14:25:09 by tbrissia          #+#    #+#             */
/*   Updated: 2022/05/12 18:08:42 by tbraquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static int	count_tab(t_token *command)
{
	int	i;

	i = 1;
	while (command[i].value)
		i++;
	return (i);
}

// Get the index of space in line.
static int	*fill_with_index(char *line, int spaces, int *ret)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (*line && spaces)
	{
		if (*line == ' ' && spaces)
		{
			ret[j] = i;
			j++;
			spaces--;
		}
		i++;
		line++;
	}
	return (ret);
}

static int	*get_spaces(char *line, t_mini *shell)
{
	char	*begin;
	int		spaces;
	int		*ret;

	spaces = shell->space_line;
	begin = line;
	ret = (int *) malloc(spaces * sizeof(int));
	if (!ret)
		return (NULL);
	while (*line && *line != ' ')
		line++;
	line++;
	if (*line == '-' && *line)
		line += 3;
	ret = fill_with_index(line, spaces, ret);
	line = begin;
	return (ret);
}

void	print_echo(t_token *cmd, int *extra, int *args, t_mini *shell)
{
	int	j;
	int	save;
	int	first_arg;

	j = 0;
	save = 0;
	first_arg = 1;
	while (cmd[extra[1]].value)
	{
		if (first_arg == 0 && extra[0] && save == args[j])
		{
			printf(" ");
			extra[0]--;
			j++;
			save += 1;
		}
		space_echo(extra, cmd, shell, &save);
		first_arg = 0;
		extra[1]++;
	}
}

void	cmd_echo(t_token *command, t_mini *shell, char *line)
{
	int	option;
	int	extra[2];
	int	*args;

	extra[0] = shell->space_line;
	option = 0;
	extra[1] = 1;
	args = get_spaces(line, shell);
	if (count_tab(command) == 1)
		return ;
	if (compare_strings(command[1].value, "-n"))
	{
		option = 1;
		extra[1]++;
	}
	print_echo(command, extra, args, shell);
	if (args)
		free(args);
	if (option == 0)
		printf("\n");
}
