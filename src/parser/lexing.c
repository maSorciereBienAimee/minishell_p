/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nayache <nayache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 18:42:19 by nayache           #+#    #+#             */
/*   Updated: 2021/06/14 16:57:34 by nayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/lexer_parser.h"

static int	get_size_occur(char *str)
{
	int		size;

	size = 1;
	if (is_space(*str) == 1)
	{
		str++;
		while (*str != '\0' && is_space(*str))
		{
			str++;
			size++;
		}
		return (size);
	}
	else if (is_text(*str) == 1)
	{
		str++;
		while (*str != '\0' && is_text(*str) && *str != BACKSLASH)
		{
			str++;
			size++;
		}
	}
	return (size);
}

static int	index_quote(char *str, char quote)
{
	int		i;

	i = 1;
	while (str[i] != '\0' && str[i] != quote)
	{
		if (quote == DQUOTE && str[i] == BACKSLASH)
		{
			if (str[i + 1] == BACKSLASH)
				i++;
			else if (str[i + 1] == DQUOTE || str[i + 1] == QUOTE)
				i++;
		}
		i++;
	}
	if (str[i] == '\0')
		return (-1);
	return (i - 1);
}

static int	lexing_quote(t_token *token, char *buf)
{
	int size;

	if ((size = index_quote(buf, *buf)) == -1)
	{
		ft_putstr_fd("minishell: syntax error: expected quote \' or \"\n", 2);
		return (-1);
	}
	if (size > 0)
		if (add_token(token, buf, *buf, size) == -1)
			return (-1);
	return (size + 2);
}

static int	tokenizer(char *buf, t_token *token)
{
	int	size;

	if (*buf == BACKSLASH)
	{
		if (*buf == BACKSLASH && *(buf + 1) == '\0')
		{
			ft_putstr_fd("minishell: syntax error: `\\`\n", 2);
			return (-1);
		}
		size = 2;
	}
	else if (*buf == QUOTE || *buf == DQUOTE)
	{
		if ((size = lexing_quote(token, buf)) == -1)
			return (-1);
	}
	else
		size = get_size_occur(buf);
	if (*buf != QUOTE && *buf != DQUOTE)
		if (add_token(token, buf, *buf, size) == -1)
			return (-1);
	return (size);
}

int			lexing(char *buf, t_token *token)
{
	int		size;

	if (*buf == '\0')
		return (0);
	else
		if ((size = tokenizer(buf, token)) == -1)
			return (-1);
	return (lexing(buf + size, token));
}
