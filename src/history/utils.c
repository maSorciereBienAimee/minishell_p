/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nayache <nayache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 13:01:10 by nayache           #+#    #+#             */
/*   Updated: 2021/06/22 15:01:55 by nayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/lexer_parser.h"

void		free_history(t_hist *history)
{
	t_hist *tmp;
	
	while (history != NULL)
	{
		if (history->cmd != NULL)
			free(history->cmd);
		tmp = history;
		history = history->next;
		free(tmp);
		tmp = NULL;
	}
}

t_hist		*init_history(int exist)
{
	t_hist	*history;

	if ((history = malloc(sizeof(t_hist))) == NULL)
		return (NULL);
	history->exist = exist;
	history->nb = 1;
	history->cmd = NULL;
	history->prev = NULL;
	history->next = NULL;
	return (history);
}

void		list_push_back(t_hist *head, t_hist *new)
{
	while (head->next != NULL)
		head = head->next;
	head->next = new;
	new->nb = head->nb + 1;
	new->prev = head;
}

int		ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while ((s1[i] != '\0' && s2[i] != '\0') && (s1[i] == s2[i]))
		i++;
	return (s1[i] - s2[i]);
}
