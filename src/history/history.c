/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nayache <nayache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 15:54:23 by nayache           #+#    #+#             */
/*   Updated: 2021/06/22 14:15:07 by nayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"
#include "../../includes/history.h"
#include "../../includes/lexer_parser.h"

void		print_history(t_hist *history)
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

int			add_line_to_history(t_hist *history, char *line)
{
	t_hist	*new;

	if (*line == '\0')
		return (0);
	if (history->cmd == NULL)
	{
		history->exist = 0;
		if ((history->cmd = ft_strdup(line)) == NULL)
			return (-1);
		return (0);
	}
	if ((new = init_history(0)) == NULL || (new->cmd = ft_strdup(line)) == NULL)
		return (-1);
	list_push_back(history, new);
	return (0);
}

static int	save_to_list(int fd, t_hist	*history)
{
	t_hist	*tmp;
	char	*line;
	int		ret;

	tmp = history;
	while ((ret = get_next_line(fd, &line)) == 1)
	{
		if (tmp->cmd != NULL)
			if ((tmp = init_history(1)) == NULL)
				return (-1);
		if (*line != '\0')
		{
			if ((tmp->cmd = ft_strdup(line)) == NULL)
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

t_hist		*build_history(int exist)
{
	t_hist	*history;
	int		fd;

	if ((history = init_history(exist)) == NULL)
		return (NULL);
	if ((fd = open(".minishell_history", O_RDONLY)) == -1)
		return (history);
	if (save_to_list(fd, history) == - 1)
	{
		close(fd);
		free_history(history);
		return (NULL);
	}
	close(fd);
	return (history);
}
