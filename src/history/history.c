/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nayache <nayache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 15:54:23 by nayache           #+#    #+#             */
/*   Updated: 2021/06/24 15:54:39 by nayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"
#include "../../includes/history.h"
#include "../../includes/lexer_parser.h"

void	print_history(t_hist *history)
{
	while (history != NULL)
	{
		if (history->cmd != NULL)
		{
			ft_putstr("     ");
			ft_putnbr(history->nb);
			ft_putchar(' ');
			ft_putstr(history->cmd);
			ft_putchar('\n');
		}
		history = history->next;
	}
}

int	add_line_to_history(t_hist *history, char *line)
{
	t_hist	*new;

	if (*line == '\0')
		return (0);
	if (history->cmd == NULL)
	{
		history->exist = 0;
		history->cmd = ft_strdup(line);
		if (history->cmd == NULL)
			return (-1);
		return (0);
	}
	new = init_history(0);
	if (new == NULL)
		return (-1);
	new->cmd = ft_strdup(line);
	if (new->cmd == NULL)
		return (-1);
	list_push_back(history, new);
	return (0);
}

static int	save_to_list(int fd, t_hist	*history)
{
	t_hist	*tmp;
	char	*line;

	tmp = history;
	while (get_next_line(fd, &line) == 1)
	{
		if (tmp->cmd != NULL)
		{
			tmp = init_history(1);
			if (tmp == NULL)
				return (-1);
		}
		if (*line != '\0')
		{
			tmp->cmd = ft_strdup(line);
			if (tmp->cmd == NULL)
				return (-1);
			if (tmp != history)
				list_push_back(history, tmp);
		}
		free(line);
	}
	if (line != NULL)
		free(line);
	return (0);
}

t_hist	*build_history(int exist)
{
	t_hist	*history;
	int		fd;

	history = init_history(exist);
	if (history == NULL)
		return (NULL);
	fd = open(".minishell_history", O_RDONLY);
	if (fd == -1)
		return (history);
	if (save_to_list(fd, history) == -1)
	{
		close(fd);
		free_history(history);
		return (NULL);
	}
	close(fd);
	return (history);
}
