/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_readline_cur.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 14:55:16 by ssar              #+#    #+#             */
/*   Updated: 2021/06/12 14:58:14 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

t_gestion_sig	g_my_sig;

int	check_touche_b(t_sh*sh, char *b, int *ij, char **str)
{
	int	k;

	k = 0;
	while (k < 4)
	{
		if (b[k] == EOF || b[k] == '\0')
			return (0);
		if (b[k] == '\n')
			return (1);
		if (b[k] != 127 && b[k] >= 32)
		{
			*str = stock_tab(sh, *str, ij[0]);
			(*str)[ij[1]] = b[k];
			(*str)[ij[0] - 1] = '\0';
			ij[0]++;
			ij[1]++;
		}
		k++;
	}
	return (0);
}

char	*my_readline(t_sh *sh)
{
	int		ij[2];
	char	*str;
	int		stop;
	int		a;
	char	buff[4];

	ij[0] = -1;
	ij[1] = 0;
	stop = 0;
	str = (char *)malloc(sizeof(char) * 1);
	if (!str)
		ft_error(sh, strerror(errno), NULL,NULL);
	str[0] = '\0';
	write(1, "> ", 2);
	while (++(ij[0]) < 4)
		buff[ij[0]] = 0;
	ij[0] = 2;
	while (stop != 1)
	{
		a = read(g_my_sig.fd_out, &buff, 4);
		if (a == 0 && buff[0] == 0)
		{
			free(str);
			return (NULL);
		}
		stop = check_touche_b(sh, buff, ij, &str);
		a = -1;
		while (++a < 4)
			buff[a] = 0;
	}
	return (str);
}

int	fill_redir_cur(char **new, char **stock, char *c)
{
	int	i;
	int	j;

	i = 0;
	if (stock != NULL)
	{
		i = -1;
		while(stock[++i])
		{
			new[i] = (char *)malloc(sizeof(char) * (ft_len(stock[i]) + 2));
			if (!new[i])
				return (-1);
			j = -1;
			while (stock[i][++j])
				new[i][j] = stock[i][j];
			new[i][j] = '\0';
		}
	}
	new[i] = (char *)malloc(sizeof(char) * (ft_len(c) + 1));
	if (!new[i])
		return (-1);
	j = -1;
	while (c[++j])
		new[i][j] = c[j];
	new[i][j] = '\0';
	return (1);
}

char	**stock_redir_cur(char **stock, char *c)
{
	int		i;
	char	**new;

	i = 0;
	if (stock == NULL)
		i = 0;
	else
	{
		while(stock[i] != 0)
			i++;
	}
	new = (char **)malloc(sizeof(char *) * (i + 2));
	if(!new)
		return (NULL);
	if (fill_redir_cur(new, stock, c) == -1)
	{
		if (stock != NULL)
			ft_free_tab(stock);
		ft_free_tab(new);
		return (NULL);
	}
	new[i + 1] = 0;
	if (stock != NULL)
		ft_free_tab(stock);
	return (new);
}

char	**get_redir_arg(t_sh *sh, char *word)
{
	char		*str;
	t_actual	*temp;
	char		**stock;
	int			stop;

	stop = 0;
	str = NULL;
	stock = NULL;
	while (stop == 0)
	{
		str = my_readline(sh);
		if (str == NULL || (ft_comp(str, word) == 0))
		{
			if (str == NULL)
				write(2, "Closed by EOF\n",14);
			stop = 1;
			break ;
		}
		stock = stock_redir_cur(stock, str);
		if (stock == NULL)
			ft_error(sh, strerror(errno), NULL, NULL);
		free(str);
	}
	if (str != NULL)
		free(str);
	return (stock);
}
