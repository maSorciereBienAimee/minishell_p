/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_in_tab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 08:40:06 by ssar              #+#    #+#             */
/*   Updated: 2021/06/03 08:40:18 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

int	copy_arg(char **dest, char **src)
{
	int	i;
	int	j;
	int	size;

	i = -1;
	while (src[++i])
	{
		j = -1;
		size = ft_len(src[i]);
		dest[i] = (char *)malloc(sizeof(char) * (size + 1));
		if (!dest[i])
		{
			ft_free_tab(dest);
			return (0);
		}
		while (src[i][++j])
			dest[i][j] = src[i][j];
		dest[i][j] = '\0';
	}
	return (i);
}

void	fill_arg(t_sh *sh, char **dest, int k, int i)
{
	int	j;
	int	size;

	i--;
	while (sh->stock_for_pipe->str_arg[++i])
	{
		j = -1;
		size = ft_len(sh->stock_for_pipe->str_arg[i]);
		dest[k] = (char *)malloc(sizeof(char) * (size + 1));
		if (!dest[k])
		{
			ft_free_tab(dest);
			dest = NULL;
			return ;
		}
		while (sh->stock_for_pipe->str_arg[i][++j])
			dest[k][j] = sh->stock_for_pipe->str_arg[i][j];
		dest[k][j] = '\0';
		k++;
	}
}

char	**add_these_arg(t_sh *sh, char **lst, int i, int allou)
{
	char	**new;
	int		size;
	int		k;

	size = 0;
	k = 0;
	if (allou != 0)
	{
		while (lst[size])
			size++;
	}
	size += sh->stock_for_pipe->arg_command;
	if (i == 1)
		size--;
	new = (char **)malloc(sizeof(char *) * (size + 1));
	if (!new)
		return (NULL);
	new[size] = 0;
	if (allou != 0)
	{
		k = copy_arg(new, lst);
		ft_free_tab(lst);
	}
	fill_arg(sh, new, k, i);
	return (new);
}

char	**all_arg(t_sh *sh)
{
	t_actual	*temp;
	int			is_rediv;
	char		**lst;
	int			ij[2];

	ij[0] = 0;
	ij[1] = 0;
	is_rediv = 0;
	temp = sh->stock_for_pipe;
	while (ij[0] == 0)
	{
		if (is_rediv == 1)
			lst = add_these_arg(sh, lst, 1, (ij[1])++);
		else
			lst = add_these_arg(sh, lst, 0, (ij[1])++);
		if (sh->stock_for_pipe->no_suite == 0 && sh->stock_for_pipe->pipe == 0)
			is_rediv = 1;
		else
			is_rediv = 0;
		if (sh->stock_for_pipe->pipe == 1 || sh->stock_for_pipe->next == NULL)
			ij[0] = 1;
		else
			sh->stock_for_pipe = sh->stock_for_pipe->next;
	}
	return (lst);
}
