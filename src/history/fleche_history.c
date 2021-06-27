/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fleche_history.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 19:32:14 by ssar              #+#    #+#             */
/*   Updated: 2021/06/27 18:04:48 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

void	replace_delete(t_sh *sh, int len)
{
	int		ligne;
	char	*s;
	int		r;
	int		rc[2];

	get_cursor(sh, rc, 0);
	r = rc[0] - 1;
	len = ft_len(sh->command) + (sh->init_cursor_c - 1);
	sh->tty_col = tgetnum("co");
	ligne = len / sh->tty_col;
	if (ligne >= 1)
	{
		if (len % sh->tty_col != 0)
			ligne++;
		r = rc[0] - ligne;
	}
	s = tgetstr("cm", NULL);
	tputs(tgoto(s, sh->init_cursor_c - 1, r), 1, ft_putchar_b);
	s = tgetstr("cd", NULL);
	tputs(s, 1, ft_putchar_b);
	if (sh->in_read == 0)
	{
		while (sh->history->next != NULL)
			sh->history = sh->history->next;
	}
}

void	fleche_haut(t_sh *sh)
{
	int	len;

	if (!sh->history)
		return ;
	replace_delete(sh, len);
	if (sh->in_read == 0)
	{
		if (sh->history != NULL)
		{
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
	sh->in_read = 1;
}

void	fleche_bas(t_sh *sh)
{
	int	len;

	if (!sh->history)
		return ;
	replace_delete(sh, len);
	if (sh->history->next != NULL)
	{
		sh->history = sh->history->next;
		write(g_my_sig.fd_out, sh->history->cmd, ft_len(sh->history->cmd));
		sh->command = copy_char(sh, sh->command, sh->history->cmd);
	}
	else
	{
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
		sh->in_read = 0;
	}
}
