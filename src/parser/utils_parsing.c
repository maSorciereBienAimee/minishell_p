/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nayache <nayache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 15:28:37 by nayache           #+#    #+#             */
/*   Updated: 2021/06/14 16:57:57 by nayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer_parser.h"

int		is_space(char c)
{
	if (c == '\r' || c == '\v' || c == '\f')
		return (1);
	if (c == '\t' || c == '\n' || c == ' ')
		return (1);
	return (0);
}

int		check_special_char(char c)
{
	if (c == PIPE || c == DIRIN || c == DIROUT)
		return (1);
	if (c == END_CMD)
		return (1);
	return (0);
}

static t_tokentype	search_type(char c)
{
	if (c == DIRIN)
		return (Dirin);
	if (c == DIROUT)
		return (Dirout);
	if (c == PIPE)
		return (Pipe);
	return (End_cmd);
}

t_tokentype			get_type(char c)
{
	if (check_special_char(c) == 1)
		return (search_type(c));
	else if (c == QUOTE)
		return (Quote_text);
	else if (c == DQUOTE)
		return (Dquote_text);
	else if (c == BACKSLASH)
		return (Escape);
	else if (is_space(c) == 1)
		return (Whitespace);
	else
		return (Text);
}

int			is_text(char c)
{
	if (is_space(c) == 1)
		return (0);
	if (c == DQUOTE || c == QUOTE)
		return (0);
	if (check_special_char(c) == 1)
		return (0);
	return (1);
}
