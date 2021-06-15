/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 16:57:01 by nayache           #+#    #+#             */
/*   Updated: 2021/06/14 17:35:29 by nayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

static int	work(char **stock, char **line, char *neww)
{
	char	*tmp;

	neww[0] = '\0';
	if (!(*line = ft_strdup(*stock)))
		return (-1);
	tmp = *stock;
	if (!(*stock = ft_strdup(neww + 1)))
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
		if (!(*line = ft_strdup(*stock)))
			return (-1);
		free(*stock);
		*stock = NULL;
	}
	else
	{
		if (!(*line = malloc(1)))
			return (-1);
		line[0][0] = '\0';
	}
	return (1);
}

static int	work_less(char **stock, char **line, int value)
{
	if ((*stock)[value - 1] == '\n')
	{
		(*stock)[value - 1] = '\0';
		return (work_zero(stock, line));
	}
	if (work_zero(stock, line) == -1)
		return (-1);
	return (0);
}

int			get_next_line(int fd, char **line)
{
	static char		*stock = NULL;
	char			buf[10000 + 1];
	char			*tmp;
	ssize_t			value;

	if (line == NULL)
		return (-1);
	if (stock != NULL && ((tmp = ft_strchr(stock, '\n')) != NULL))
		return (work(&stock, line, tmp));
	if ((value = read(fd, buf, 10000)) > 0)
	{
		buf[value] = '\0';
		if (!(tmp = ft_strjoin(stock, buf)))
			return (-1);
		if (stock != NULL)
			free(stock);
		stock = tmp;
		if (value < 10000)
			return (work_less(&stock, line, value));
		return (get_next_line(fd, line));
	}
	if (value == 0)
		if ((work_zero(&stock, line)) == -1)
			return (-1);
	return (value);
}
