/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lblanche <lblanche@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 15:15:23 by lblanche          #+#    #+#             */
/*   Updated: 2022/05/03 17:34:51 by tbrissia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

enum	e_type
{
	WORD,
	OPTION,
	REDIR,
	REDIR_APPEND,
	INFILE,
	HEREDOC,
	PIPE,
	SQUOTE,
	DQUOTE
};

typedef struct s_token
{
	enum e_type	type;
	char		*value;
}	t_token;

#endif
