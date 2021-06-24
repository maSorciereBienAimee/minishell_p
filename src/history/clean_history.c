/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_history.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nayache <nayache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 14:43:10 by nayache           #+#    #+#             */
/*   Updated: 2021/06/24 16:07:21 by nayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/history.h"

void	clean_elem(t_hist *elem)
{
	if (elem->cmd != NULL)
	{
		free(elem->cmd);
		elem->cmd = NULL;
	}
	elem->exist = 0;
	elem->nb = 1;
	elem->prev = NULL;
	elem->next = NULL;
}

void	clean_history(t_hist *history)
{
	t_hist	*head;
	t_hist	*tmp;

	head = history;
	while (history != NULL)
	{
		tmp = history;
		history = history->next;
		clean_elem(tmp);
		if (tmp != head)
			free(tmp);
	}
}
