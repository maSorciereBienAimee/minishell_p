/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fleche_history.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 19:32:14 by ssar              #+#    #+#             */
/*   Updated: 2021/06/22 14:49:20 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

void	fleche_haut(t_sh *sh)
{
	int len;

	if (!sh->history)
		return ;
	if (sh->in_read == 0)
	{
		while (sh->history->next != NULL)
			sh->history = sh->history->next;
		if (sh->history != NULL)
		{
			len = ft_len(sh->command);
			while (len >= 0)
				write(g_my_sig.fd_out, "\b\0\b", 3);
			write(g_my_sig.fd_out, sh->history->cmd, ft_len(sh->history->cmd));
			sh->command = copy_char(sh, sh->command, sh->history->cmd);
		}
	}
	else
	{
		if (sh->history->prev != NULL)
			sh->history = sh->history->prev;
		if (sh->history != NULL)
		{
			write(g_my_sig.fd_out, sh->history->cmd, ft_len(sh->history->cmd));
			sh->command = copy_char(sh, sh->command, sh->history->cmd);
		}
	}
}

void	fleche_bas(t_sh *sh)
{
	int len;

	if (!sh->history)
		return ;
	if (sh->history->next != NULL)
	{
		sh->history = sh->history->next;
		len = ft_len(sh->command);
		while (len >= 0)
			write(g_my_sig.fd_out, "\b\0\b", 3);
		write(g_my_sig.fd_out, sh->history->cmd, ft_len(sh->history->cmd));
		sh->command = copy_char(sh, sh->command, sh->history->cmd);
	}
	else
	{
		len = ft_len(sh->command);
		while (len >= 0)
			write(g_my_sig.fd_out, "\b\0\b", 3);
		free(sh->command);
		sh->alloue[1] = 0;
		sh->command = (char *)malloc(sizeof(char) * 1);
		if (!sh->command)
		{
			ft_error(sh, strerror(errno), NULL, NULL);
			return ;
		}
		sh->alloue[1] = 1;
		sh->command[0] = '\0';
	}
}
