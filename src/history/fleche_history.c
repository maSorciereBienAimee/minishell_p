/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fleche_history.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 19:32:14 by ssar              #+#    #+#             */
/*   Updated: 2021/06/23 19:20:55 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

/*
 il faut :
 stocker la ou mettre la commande -> fait dans read_cmd.c
 ensuite, effacer tous les caractere jusqu'au prompt
 ensuite ecrire la nouvelle ligne
 deplacer le curseur a la fin de la nouvelle ligne ?
 remplacer sh->command par la nouvelle (normalement deja fait)
 */

void	fleche_haut(t_sh *sh)
{
	int len;
	int rc[2];
	int ligne;
char *s;
//	get_cursor(sh, rc, 0);
//	ligne = rc[0] - sh->init_cursor_r;
//	printf("");
//if (ligne > 1)
//{	s = tgetstr("cm", NULL);
//	tputs(tgoto(s, 1, sh->init_cursor_r + 1), 1, ft_putchar_b);
//	s = tgetstr("dl", NULL);
//		tputs(s, ligne, ft_putchar_b);
//}
int i ;
i = ft_len(sh->command);
while (i>0)
{
	//printf("rentre\n");
		get_cursor(sh, rc, 0);
				sh->tty_row = tgetnum("li");
				sh->tty_col = tgetnum("co");
				if (rc[1] == 1)
				{
					rc[0] = rc[0] - 2;
					s = tgetstr("cm", NULL);
					tputs(tgoto(s, sh->tty_col, rc[0]), 1, ft_putchar_b);
				}
				else
					write(g_my_sig.fd_out, "\b",1);
				s = tgetstr("dc", NULL);
				tputs(s, 1, ft_putchar_b);
i--;
}
		get_cursor(sh, rc, 0);
	//s = tgetstr("cm", NULL);
//tputs(tgoto(s, rc[1], rc[0]), 1, ft_putchar_b);
/*
while (rc[0] != sh->init_cursor_r && rc[1] != sh->init_cursor_c)
{
//        printf("rentre\n");
                                sh->tty_row = tgetnum("li");
                                sh->tty_col = tgetnum("co");
                                if (rc[1] == 1)
                                {
                                        rc[0] = rc[0] - 2;
                                        s = tgetstr("cm", NULL);
                                        tputs(tgoto(s, sh->tty_col, rc[0]), 1, ft_putchar_b);
                                }
                                else
                                        write(g_my_sig.fd_out, "\b",1);
                                s = tgetstr("dc", NULL);
                                tputs(s, 1, ft_putchar_b);
                get_cursor(sh, rc, 0);
}
*/
//	s = tgetstr("cm", NULL);
//tputs(tgoto(s, sh->init_cursor_c, sh->init_cursor_r), 1, ft_putchar_b);
//s = tgetstr("ce", NULL);
//		tputs(s, 1, ft_putchar_b);
//s = tgetstr("dc", NULL);
//		tputs(s, 1, ft_putchar_b);
//	if (!sh->history)
//		return ;
	if (sh->in_read == 0)
	{
		while (sh->history->next != NULL)
			sh->history = sh->history->next;
		if (sh->history != NULL)
		{
		//len = ft_len(sh->command);
		//	while (len >= 0)
		//		write(g_my_sig.fd_out, "\b\0\b", 3);
			write(0, sh->history->cmd, ft_len(sh->history->cmd));
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
int i ;
        int rc[2];
        int ligne;
char *s;

i = ft_len(sh->command);
                get_cursor(sh, rc, 0);
while (rc[0] != sh->init_cursor_r && rc[1] != sh->init_cursor_c)
{
  //      printf("rentre\n");
                                sh->tty_row = tgetnum("li");
                                sh->tty_col = tgetnum("co");
                                if (rc[1] == 1)
                                {
                                        rc[0] = rc[0] - 2;
                                        s = tgetstr("cm", NULL);
                                        tputs(tgoto(s, sh->tty_col, rc[0]), 1, ft_putchar_b);
                                }
                                else
                                        write(g_my_sig.fd_out, "\b",1);
                                s = tgetstr("dc", NULL);
                                tputs(s, 1, ft_putchar_b);
                get_cursor(sh, rc, 0);
}
        s = tgetstr("cm", NULL);
tputs(tgoto(s, sh->init_cursor_c, sh->init_cursor_r), 1, ft_putchar_b);
s = tgetstr("ce", NULL);
                tputs(s, 1, ft_putchar_b);
s = tgetstr("dc", NULL);
                tputs(s, 1, ft_putchar_b);

//	if (!sh->history)
//		return ;
	if (sh->history->next != NULL)
	{
		sh->history = sh->history->next;
	//	len = ft_len(sh->command);
	//	while (len >= 0)
	//		write(g_my_sig.fd_out, "\b\0\b", 3);
		write(g_my_sig.fd_out, sh->history->cmd, ft_len(sh->history->cmd));
		sh->command = copy_char(sh, sh->command, sh->history->cmd);
	}
	else
	{
	//	len = ft_len(sh->command);
	//	while (len >= 0)
	//		write(g_my_sig.fd_out, "\b\0\b", 3);
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
