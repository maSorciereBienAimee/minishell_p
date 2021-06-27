/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 11:33:36 by ssar              #+#    #+#             */
/*   Updated: 2021/06/27 16:40:08 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"
#include "../../includes/lexer_parser.h"

t_gestion_sig	g_my_sig;

int	read_quit(t_sh *sh, int a, char *buff)
{
	if (buff[0] == 3)
	{
		sh->in_read = 0;
		tcsetattr(0, TCSANOW, &sh->old_tty);
		write(2, "^C", 2);
		kill(0, SIGINT);
		sh->alloue[11] = 0;
		sh->last_exit = 130;
		g_my_sig.restart = 1;
		return (-1);
	}
	if (buff[0] == 4 && ft_comp("", sh->command) == 0)
	{
		tcsetattr(0, TCSANOW, &sh->old_tty);
		my_free(sh);
		my_exit_final(sh);
	}
	return (1);
}

int	prepare_command(t_sh *sh)
{
	while (sh->history->prev != NULL)
		sh->history = sh->history->prev;
	sh->in_read = 0;
	tcsetattr(0, TCSANOW, &sh->old_tty);
	add_line_to_history(sh->history, sh->command);
	if (start_parsing(sh->command) == -1)
		return (-1);
	sh->spl = ft_split_commande(sh, sh->command, ';');
	get_redir_cur(sh);
	return (0);
}

int	get_command(t_sh *sh)
{
	int		ij[2];
	int		stop;
	int		a;
	char	buff[4];

	ij[0] = -1;
	ij[1] = 0;
	stop = 0;
	write(2, "minishell $> ", 14);
	while (++(ij[0]) < 4)
		buff[ij[0]] = 0;
	ij[0] = 2;
	pass_non_canonique(sh);
	while (stop != 1)
	{
		a = read(g_my_sig.fd_out, &buff, 4);
		if (read_quit(sh, a, buff) == -1)
			return (0);
		stop = check_touche(sh, buff, &ij[1], &ij[0]);
		a = -1;
		while (++a < 4)
			buff[a] = 0;
	}
	return (prepare_command(sh));
}
