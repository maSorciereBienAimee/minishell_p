/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 16:57:01 by nayache           #+#    #+#             */
/*   Updated: 2021/06/24 16:25:42 by nayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/lexer_parser.h"

static int	work(char **stock, char **line, char *neww)
{
	char	*tmp;

	neww[0] = '\0';
	*line = ft_strdup(*stock);
	if (*line == NULL)
		return (-1);
	tmp = *stock;
	*stock = ft_strdup(neww + 1);
	if (*stock == NULL)
	{
		free(*line);
		free(tmp);
		return (-1);
	}
	free(tmp);
	return (1);
}

static int	work_zero(char **stock, char **line)
{
	if (*stock != NULL)
	{
		*line = ft_strdup(*stock);
		if (*line == NULL)
			return (-1);
		free(*stock);
		*stock = NULL;
	}
	else
	{
		*line = malloc(1);
		if (*line == NULL)
			return (-1);
		line[0][0] = '\0';
	}
	return (1);
}

int	end_value(int value, char **stock, char **line)
{
	if (value == 0)
		if ((work_zero(stock, line)) == -1)
			return (-1);
	return (value);
}

int	get_next_line(int fd, char **line)
{
	static char		*stock = NULL;
	char			buf[1 + 1];
	char			*tmp;
	ssize_t			value;

	if (line == NULL)
		return (-1);
	if (stock != NULL)
	{
		tmp = ft_strchr(stock, '\n');
		if (tmp != NULL)
			return (work(&stock, line, tmp));
	}
	value = read(fd, buf, 1);
	if (value > 0)
	{
		buf[value] = '\0';
		tmp = ft_strjoin(stock, buf);
		if (stock != NULL)
			free(stock);
		stock = tmp;
		return (get_next_line(fd, line));
	}
	return (end_value(value, &stock, line));
}
