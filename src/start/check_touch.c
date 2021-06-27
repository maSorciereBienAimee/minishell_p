/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_touch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 17:04:35 by ssar              #+#    #+#             */
/*   Updated: 2021/06/27 17:49:33 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

void	print_del(t_sh *sh, int *j, int *i)
{
	int		rc[2];
	char	*s;
	int		new_row;

	if (*j - 1 >= 0)
	{
		sh->command[*j - 1] = 0;
		*j -= 1;
		*i -= 1;
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
			write(g_my_sig.fd_out, "\b", 1);
		s = tgetstr("dc", NULL);
		tputs(s, 1, ft_putchar_b);
	}
	else
		return ;
}

void	print_letter(t_sh *sh, char b, int *j, int *i)
{
	if (b >= 32)
	{
		if (b == 127)
			print_del(sh, j, i);
		else
		{
			write(g_my_sig.fd_out, &b, 1);
			sh->command = stock_tab(sh, sh->command, *i);
			sh->command[*j] = b;
			sh->command[*i - 1] = '\0';
			(*i)++;
			(*j)++;
		}
	}
}

void	envoi_fleche(t_sh *sh, char *b, int k)
{
	if (b[k + 2] && b[k + 2] == 65)
		fleche_haut(sh);
	if (b[k + 2] && b[k + 2] == 66)
		fleche_bas(sh);
}

int	check_touche(t_sh*sh, char *b, int *j, int *i)
{
	int	k;
	int	rc[2];

	k = 0;
	while (k < 4)
	{
		if (b[k] == '\n' || (b[k] == 4 && ft_comp("", sh->command) == 0))
		{
			write(g_my_sig.fd_out, "\n\r", 2);
			return (1);
		}
		else if (b[k] == 28)
			return (0);
		else if (b[k] == 27)
		{
			envoi_fleche(sh, b, k);
			(*j) = ft_len(sh->command);
			(*i) = ft_len(sh->command) + 2;
			return (0);
		}
		else
			print_letter(sh, b[k], j, i);
		k++;
	}
	return (0);
}
