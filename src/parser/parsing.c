/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nayache <nayache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 18:33:26 by nayache           #+#    #+#             */
/*   Updated: 2021/06/14 16:57:46 by nayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/lexer_parser.h"

static int	adjust_type(t_tokentype type)
{
	if (type == Dquote_text || type == Quote_text || type == Escape)
		return (Text);
	if (type == Pipe)
		return (4);
	return (type);
}

static int  state_machine(t_state state, t_tokentype type)
{
	const int	machine[5][6] =
	{
		{EAT, START, ERROR, ERROR, ERROR, ERROR},
		{EAT, EAT, INPUT, OUTPUT, FLUX, START},
		{EAT, EAT, PIPE, ERROR, ERROR, ERROR},
		{EAT, EAT, ERROR, PIPE, ERROR, ERROR},
		{EAT, EAT, ERROR, ERROR, ERROR, ERROR},
	};
	type = adjust_type(type);
	return (machine[state][type]);
}

static void	print_syntax_error(t_tokentype old_type, t_tokentype type)
{
	ft_putstr_fd("minishell : ", 2);
	if (type == Dirin)
			ft_putstr_fd("syntax error : near unexpected token `<'\n", 2);
	if (type == Dirout)
			ft_putstr_fd("syntax error : near unexpected token `>'\n", 2);
	if (type == Pipe)
	{
		if (old_type == type)	
			ft_putstr_fd("syntax error : near unexpected token `||'\n", 2);
		else
			ft_putstr_fd("syntax error : near unexpected token `|'\n", 2);
	}
	if (type == End_cmd)
	{
		if (old_type == type)
			ft_putstr_fd("syntax error : near unexpected token `;;'\n", 2);
		else
			ft_putstr_fd("syntax error : near unexpected token `;'\n", 2);
	}
}

int			parsing(t_token *token)
{
	t_token		*tmp;
	t_state		current_state;
	t_tokentype old_type;

	current_state = START;
	old_type = -1;
	tmp = token;
	while (tmp != NULL && tmp->data != NULL)
	{
		current_state = state_machine(current_state, tmp->type);
		if (current_state == ERROR)
		{
			print_syntax_error(old_type, tmp->type);
			return (-1);
		}
		old_type = tmp->type;
		tmp = tmp->next;
	}
	if (current_state != START && current_state != EAT)
	{
		print_syntax_error(-1, old_type);
		return (-1);
	}
	return (0);	
}
