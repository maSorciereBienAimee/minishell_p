/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_basic_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 16:17:55 by ssar              #+#    #+#             */
/*   Updated: 2021/06/12 14:42:51 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

t_redir_cur	*ft_lstlast_red(t_redir_cur *lst)
{
	if (!lst)
		return (0);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	lst_add_back_arg_red(t_arg_redir **last, t_arg_redir *new_lst)
{
	t_arg_redir	*temp;

	if (!new_lst)
		return ;
	if (!*last)
	{
		*last = new_lst;
		return ;
	}
	temp = ft_lstlast_arg_redir(*last);
	temp->next = new_lst;
}

void	lst_add_back_red(t_redir_cur **last, t_redir_cur *new_lst)
{
	t_redir_cur	*temp;

	if (!new_lst)
		return ;
	if (!*last)
	{
		*last = new_lst;
		return ;
	}
	temp = ft_lstlast_red(*last);
	temp->next = new_lst;
}

t_list_env	*ft_lstlast(t_list_env *lst)
{
	if (!lst)
		return (0);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	lst_add_back(t_list_env **last, t_list_env *new_lst)
{
	t_list_env	*temp;

	if (!new_lst)
		return ;
	if (!*last)
	{
		*last = new_lst;
		return ;
	}
	temp = ft_lstlast(*last);
	temp->next = new_lst;
}

