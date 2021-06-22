/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_history.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nayache <nayache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 14:07:29 by nayache           #+#    #+#             */
/*   Updated: 2021/06/22 14:39:10 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"
#include "../../includes/history.h"
#include "../../includes/lexer_parser.h"

static void	check_nl(int fd, int *new_line)
{
	char	buf[1];
	char	memo;

	if (read(fd, &buf, 1) == 0)
		return ;
	else
	{
		memo = *buf;
		while (read(fd, &buf, 1) == 1)
			memo = *buf;
		if (memo == '\n')
			*new_line = 1;
	}
}

static int	open_history(int fd, int *new_line)
{
	*new_line = 0;
	fd = open(".minishell_history", O_RDONLY);
	if (fd == -1)
	{
		*new_line = 1;
		fd = open(".minishell_history", O_RDWR | O_CREAT, S_IRWXU);
		return (fd);
	}
	check_nl(fd, new_line);
	close(fd);
	fd = open(".minishell_history", O_RDWR | O_APPEND, S_IRWXU);
	return (fd);
}

void		write_history(t_hist *history)
{
	int fd;
	int	new_line;

	if ((fd = open_history(fd, &new_line)) == -1)
	{
		ft_putstr_fd("Error, failed to open `.minishell_history' file\n", 2);
		return;
	}
	if (new_line == 0)
		write(fd, "\n", 1);
	while (history != NULL)
	{
		if (history->exist == 0 && history->cmd != NULL)
		{
			ft_putstr_fd(history->cmd, fd);
			write(fd, "\n", 1);
		}
		history = history->next;
	}
	close(fd);
}
