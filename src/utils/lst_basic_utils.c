/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_basic_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 14:32:12 by ssar              #+#    #+#             */
/*   Updated: 2021/06/12 14:38:48 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

int	ft_len_list(t_list_env *var)
{
	int	i;

	while (var->next != NULL)
	{
		i++;
		var = var->next;
	}
	return (i);
}

t_arg_redir	*ft_lstlast_arg_redir(t_arg_redir *lst)
{
	if (!lst)
		return (0);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

t_actual	*ft_lstlast_cmd(t_actual *lst)
{
	if (!lst)
		return (0);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	lst_add_back_cmd(t_actual **last, t_actual *new_lst)
{
	t_actual	*temp;

	if (!new_lst)
		return ;
	if (!*last)
	{
		*last = new_lst;
		return ;
	}
	temp = ft_lstlast_cmd(*last);
	temp->next = new_lst;
}
