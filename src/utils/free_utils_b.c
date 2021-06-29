/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils_b.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 16:03:25 by ssar              #+#    #+#             */
/*   Updated: 2021/06/29 16:05:00 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

void	ft_free_list_arg_redir(t_arg_redir **lst)
{
	t_arg_redir	*temp;

	if (!(*lst))
		return ;
	while ((*lst)->prev != NULL)
		(*lst) = (*lst)->prev;
	while (*lst)
	{
		temp = (*lst)->next;
		if ((*lst)->str != NULL)
			ft_free_tab((*lst)->str);
		free(*lst);
		*lst = temp;
	}
	lst = 0;
}

void	ft_free_list_red(t_redir_cur **lst)
{
	t_redir_cur	*temp;

	if (!(*lst))
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		ft_free_list_arg_redir(&(*lst)->arg);
		free(*lst);
		*lst = temp;
	}
	lst = 0;
}

void	ft_free_lst_cmd(t_actual **lst)
{
	t_actual	*temp;

	if (!(*lst))
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		ft_free_tab((*lst)->str_arg);
		ft_free_tab((*lst)->str_wenv);
		free(*lst);
		*lst = temp;
	}
	lst = 0;
}
