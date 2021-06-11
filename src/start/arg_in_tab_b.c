/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_in_tab_b.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 08:40:06 by ssar              #+#    #+#             */
/*   Updated: 2021/06/08 20:48:43 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

void	fill_arg_b(t_sh *sh, char **dest, int *ij, t_actual *stock)
{
	int	j;
	int	size;

	(ij[2])--;
	while (stock->str_arg[++(ij[2])])
	{
		j = -1;
		size = ft_len(stock->str_arg[ij[2]]);
		dest[ij[3]] = (char *)malloc(sizeof(char) * (size + 1));
		if (!dest[ij[3]])
		{
			ft_free_tab(dest);
			dest = NULL;
			return ;
		}
		while (stock->str_arg[ij[2]][++j])
			dest[ij[3]][j] = stock->str_arg[ij[2]][j];
		dest[ij[3]][j] = '\0';
		(ij[3])++;
	}
}

char	**add_these_arg_b(t_sh *sh, char **lst, int *ij, t_actual *stock)
{
	char	**new;
	int		size;
	int		k;

	size = 0;
	ij[3] = 0;
	if (ij[1] != 0)
	{
		while (lst[size])
			size++;
	}
	size += stock->arg_command;
	if (ij[2] == 1)
		size--;
	new = (char **)malloc(sizeof(char *) * (size + 1));
	if (!new)
		return (NULL);
	new[size] = 0;
	if (ij[1] != 0)
	{
		ij[3] = copy_arg(new, lst);
		ft_free_tab(lst);
	}
	fill_arg_b(sh, new, ij, stock);
	return (new);
}

char	**all_arg_b(t_sh *sh, t_actual *stock)
{
	int			is_rediv;
	char		**lst;
	int			ij[4];

	ij[0] = 0;
	ij[1] = 0;
	is_rediv = 0;
	while (ij[0] == 0)
	{
		if (is_rediv == 1)
			ij[2] = 1;
		else
			ij[2] = 0;
		lst = add_these_arg_b(sh, lst, ij, stock);
		(ij[1])++;
		if (stock->no_suite == 0 && stock->pipe == 0)
			is_rediv = 1;
		else
			is_rediv = 0;
		if (stock->pipe == 1 || stock->next == NULL)
			ij[0] = 1;
		else
			stock = stock->next;
	}
	return (lst);
}
