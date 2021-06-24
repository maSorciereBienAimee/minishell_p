/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_position.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 08:55:42 by ssar              #+#    #+#             */
/*   Updated: 2021/06/24 16:57:29 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

int	ft_putchar_b(int c)
{
	write(1, &c, 4);
	return (1);
}

char	*add_stock(char c, char *str)
{
	char *new;
	int i;

	if (str == NULL)
	{
		new = (char *)malloc(sizeof(char) * 2);
		if (!new)
			return (NULL);
		new[0] = c;
		new[1] = '\0';
	}
	else
	{
		i = -1;
		new = (char *)malloc(sizeof(char) * (ft_len(str) + 2));
		if (!new)
			return (NULL);
		while (str[++i])
			new[i] = str[i];
		new[i] = c;
		new[++i] = '\0';
		free(str);
	}
	return (new);
}

int	get_column(char *str)
{
	int i;
	int colonne;;

	i = 0;
	while(str[i] != ';')
		i++;
	i++;
	colonne = ft_atoi(&str[i]);
	return (colonne);
}
int	get_row(char *str)
{
	int i;
	int row;

	i =0;
	while(str[i] != '[')
		i++;
	i++;
	row = ft_atoi(&str[i]);
	return (row);
}

int	get_cursor(t_sh *sh, int *rc, int del)
{
	char buff[1];
	int stop;
	char *stock;
	char *s;

	stock = NULL;
	stop = 0;
	write(1, "\033[6n", 4);
	while (stop == 0)
	{
		read(0, &buff, 1);
		stock= add_stock(buff[0], stock);
		if (buff[0] == 'R')
			stop = 1;
		buff[0] = '0';
	}
	rc[0] = get_row(stock);
	rc[1] = get_column(stock);
	free(stock);
	return (1);
}
