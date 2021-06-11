/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 16:35:12 by ssar              #+#    #+#             */
/*   Updated: 2021/06/10 23:36:30 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

t_gestion_sig	g_my_sig;

void	ft_free_list_arg_redir(t_arg_redir **lst)
{
	t_arg_redir	*temp;

	if (!(*lst))
		return ;
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
		if ((*lst)->arg != NULL)
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
		free(*lst);
		*lst = temp;
	}
	lst = 0;
}

void	ft_free_list(t_list_env **lst)
{
	t_list_env	*temp_lst;

	if (!(*lst))
		return ;
	while (*lst)
	{
		temp_lst = (*lst)->next;
		free((*lst)->name);
		free((*lst)->value);
		free(*lst);
		*lst = temp_lst;
	}
	lst = 0;
}

void	my_free_bis(t_sh *sh)
{
	if (sh->alloue[10] == 1)
	{
		sh->actu = sh->stock_actu;
		ft_free_lst_cmd(&sh->actu);
	}
	sh->alloue[10] = 0;
	if (sh->alloue[11] == 1)
		close(g_my_sig.fd_out);
	sh->alloue[10] = 0;
	if (sh->fd_pipe[0] != 0)
		close(sh->fd_pipe[0]);
	if (sh->fd_pipe[1] != 0)
		close(sh->fd_pipe[1]);
	if (sh->fd_redir[0] != 0)
		close(sh->fd_redir[0]);
	if (sh->fd_redir[1] != 0)
		close(sh->fd_redir[1]);
	if (sh->alloue[12] != 0)
	{
		sh->redir->arg = sh->stock_redir_arg;
		sh->redir = sh->stock_redir;
		ft_free_list_red(&sh->redir);
	}
}

void	my_free(t_sh *sh)
{
	if (sh->alloue[0] == 1)
		free(sh->path);
	sh->alloue[0] = 0;
	if (sh->alloue[1] == 1)
		free(sh->command);
	sh->alloue[1] = 0;
	if (sh->alloue[2] == 1)
		ft_free_tab(sh->spl);
	sh->alloue[2] = 0;
	if (sh->alloue[4] == 1)
		ft_free_list(&sh->var_env);
	sh->alloue[4] = 0;
	if (sh->alloue[6] == 1)
		free(sh->result);
	sh->alloue[6] = 0;
	if (sh->alloue[7] == 1 && sh->parent == 0)
	{
		ft_free_tab(sh->tab_env);
		sh->alloue[7] = 0;
	}
	my_free_bis(sh);
}
