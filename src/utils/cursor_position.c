/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_position.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 08:55:42 by ssar              #+#    #+#             */
/*   Updated: 2021/06/23 14:23:47 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

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

int	replace_cursor(t_sh *sh, int del, int *rc)
{
	char *s;
//	sh->tty_row = tgetnum("li");
//	sh->tty_col = tgetnum("co");
//	if (rc[1] == 1)
//	{
//		if (rc[0] > 1)
//			rc[0] = rc[0] - 1;
//		s = tgetstr("cm", NULL);
//		tputs(tgoto(s, sh->tty_col, rc[0]), 1, ft_putchar_b);
//	}
	if (del == 1)
	{
		free(sh->command);
		sh->alloue[1] = 0;
		sh->command = (char *)malloc(sizeof(char) * 1);
		if (!sh->command)
		{
			ft_error(sh, strerror(errno), NULL, NULL);
			return (-1);
		}
		sh->alloue[1] = 1;
		sh->command[0] = '\0';
	}
	return (1);
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
	if (replace_cursor(sh, del, rc) == -1)
		return (-1);
	return (1);
}
