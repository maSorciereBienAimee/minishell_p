/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stock_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 20:07:02 by ssar              #+#    #+#             */
/*   Updated: 2021/06/24 15:07:44 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

char	*fill_bis(char *str, char *c)
{
	char	*new;
	int		j;

	if (str != NULL)
		free(str);
	if (c != NULL)
	{
		new = (char *)malloc(sizeof(char) * (ft_len(c) + 1));
		if (!new)
			return (NULL);
		j = -1;
		while (c[++j])
			new[j] = c[j];
		new[j] = '\0';
		return (new);
	}
	return (NULL);
}

int	fill_redir_cur(char **new, char **stock, char *c)
{
	int	i;
	int	j;

	i = 0;
	if (stock != NULL)
	{
		i = -1;
		while (stock[++i])
		{
			new[i] = (char *)malloc(sizeof(char) * (ft_len(stock[i]) + 1));
			if (!new[i])
				return (-1);
			j = -1;
			while (stock[i][++j])
				new[i][j] = stock[i][j];
			new[i][j] = '\0';
		}
	}
	new[i] = fill_bis(NULL, c);
	if (!new[i])
		return (-1);
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
		while (stock[i] != 0)
			i++;
	}
	new = (char **)malloc(sizeof(char *) * (i + 2));
	if (!new)
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

char	**get_redir_arg(t_sh *sh, char *word, int stop)
{
	char		*str;
	char		**stock;
	char	*new_word;

	str = NULL;
	stock = NULL;
	new_word = parse_delimiteur(sh, word);
	while (stop == 0)
	{
		str = my_readline(sh);
		if (str == NULL || (ft_comp(str, new_word) == 0))
		{
			stop = 1;
			break ;
		}
		stock = stock_redir_cur(stock, str);
		if (stock == NULL)
			ft_error(sh, strerror(errno), NULL, NULL);
		free(str);
	}
	free(new_word);
	fill_bis(str, NULL);
	parse_redir(sh, word, stock);
	//check_if_quote(word, stock); a mettre dans ffill_bis
	//{
	//	int i;
	//
	//	i = 0;
	//	while (stock[i])
	//	{
	//		check_quote_redir(word, );
	//	}
	//}
	//dans check redir quote, verifier pour tout le tableau;
	return (stock);
}
