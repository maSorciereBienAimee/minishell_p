/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nayache <nayache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 17:36:20 by nayache           #+#    #+#             */
/*   Updated: 2021/06/18 23:23:34 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	print_data_history(int *memo_nl, char buf, int *number_cmd)
{
	if (*memo_nl == 1)
	{
		*memo_nl = 0;
		ft_putstr("     ");
		ft_putnbr(*number_cmd);
		ft_putstr(" ");
		*number_cmd = *number_cmd + 1;
	}
	if (buf == '\n')
		*memo_nl = 1;
	write(1, &buf, 1);
}

void	print_history(void)
{
	char	buf[1];
	int		fd;
	int		number_cmd;
	int		memo_nl;

	fd = open(".minishell_history", O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("`.minishell_history' not found\n", 2);
		return ;
	}
	memo_nl = 0;
	number_cmd = 1;
	ft_putstr("     1 ");
	while (read(fd, &buf, 1) == 1 && *buf != '\0')
		print_data_history(&memo_nl, *buf, &number_cmd);
	ft_putchar('\n');
}

static int	open_history(int fd, int *exist)
{
	char	buf[1];

	*exist = 0;
	fd = open(".minishell_history", O_RDWR | O_APPEND, S_IRWXU);
	if (fd == -1)
	{
		fd = open(".minishell_history", O_RDWR | O_CREAT, S_IRWXU);
		return (fd);
	}
	if (read(fd, &buf, 1) == 0)
		return (fd);
	*exist = 1;
	close(fd);
	fd = open(".minishell_history", O_RDWR | O_APPEND, S_IRWXU);
	return (fd);
}

int	save_history(char *line)
{
	int	fd;
	int	exist;
	int	number_cmd;

	fd = open_history(fd, &exist);
	if (exist == 1 && *line != '\0')
		write(fd, "\n", 1);
	if (*line != '\n')
		ft_putstr_fd(line, fd);
	close(fd);
	return (0);
}
