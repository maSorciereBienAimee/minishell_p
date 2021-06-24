/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nayache <nayache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 14:56:05 by nayache           #+#    #+#             */
/*   Updated: 2021/06/24 16:26:06 by nayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/lexer_parser.h"

void	print_token(t_token *list)
{
	const char	type[9][15] = {"Text", "Whitespace", "Dirin", "Dirout",
		"Pipe", "End_cmd", "Escape", "Quote_text", "Dquote_text"};

	ft_putstr("----------------------print-token---------------------------\n");
	if (list->data == NULL)
		ft_putstr("No tokens.\n");
	while (list != NULL)
	{
		if (list->data != NULL)
		{
			printf("%s : [%s]\n", type[list->type], list->data);
		}
		list = list->next;
	}
	ft_putstr("------------------------------------------------------------\n");
}

t_token	*init_token(char *insert)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	if (insert == NULL)
		token->data = NULL;
	else
	{
		token->data = ft_strdup(insert);
		if (token->data == NULL)
			return (NULL);
	}
	token->prev = NULL;
	token->next = NULL;
	return (token);
}

void	lst_push_back(t_token *list, t_token *new)
{
	while (list->next != NULL)
		list = list->next;
	list->next = new;
	new->prev = list;
}

int	add_token(t_token *list, char *item, char first, int size)
{
	t_token		*new;
	t_tokentype	value;
	char		tmp;

	if (first == QUOTE || first == DQUOTE)
		item++;
	tmp = item[size];
	item[size] = '\0';
	value = get_type(first);
	if (list->data == NULL)
	{
		list->data = ft_strdup(item);
		list->type = value;
		item[size] = tmp;
		return (0);
	}
	new = init_token(item);
	if (new == NULL)
		return (-1);
	lst_push_back(list, new);
	new->type = value;
	if (tmp != QUOTE || tmp != DQUOTE)
		item[size] = tmp;
	return (0);
}

void	free_token(t_token *list)
{
	t_token	*tmp;

	while (list != NULL)
	{
		if (list->data != NULL)
			free(list->data);
		tmp = list;
		list = list->next;
		free(tmp);
		tmp = NULL;
	}
}
