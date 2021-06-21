/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 11:33:36 by ssar              #+#    #+#             */
/*   Updated: 2021/06/21 18:09:38 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"
#include "../../includes/lexer_parser.h"

t_gestion_sig	g_my_sig;

void	print_letter(t_sh *sh, char b, int *j, int *i)
{
	if (b >= 32)
	{
		if (b == 127)
		{
			if (sh->command[*j - 1])
			{
				write(g_my_sig.fd_out, "\b \b", 3);
				sh->command[*j - 1] = 0;
				*j -= 1;
				*i -= 1;
			}
		}
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

int	check_touche(t_sh*sh, char *b, int *j, int *i)
{
	int	k;

	k = 0;
	while (k < 4)
	{
		if (b[k] == '\n' || b[k] == 4)
		{
			write(g_my_sig.fd_out, "\n\r", 2);
			return (1);
		}
		else if (b[k] == 28)
			return (0);
		else if (b[k] == 27)
		{
			if (b[k + 2] && b[k + 2] == 65)
				write(g_my_sig.fd_out, "touche haut ", 13);
			if (b[k + 2] && b[k + 2] == 66)
				write(g_my_sig.fd_out, "touche bas ", 12);
			return (0);
		}
		print_letter(sh, b[k], j, i);
		k++;
	}
	return (0);
}

int	read_quit(t_sh *sh, int a, char *buff)
{
	if (buff[0] == 3)
	{
		tcsetattr(0, TCSANOW, &sh->old_tty);
		if (ft_comp("", sh->command) != 0)
			write(g_my_sig.fd_out, "\n", 1);
		write(g_my_sig.fd_out, "^C", 2);
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
		if (sh->alloue[7] == 1)
		{
			ft_free_tab(sh->tab_env);
		}
		sh->alloue[7] = 0;
		close(sh->save_stdout);
		exit(sh->last_exit);
	}
	return (1);
}

int	prepare_command(t_sh *sh)
{
	save_history(sh->command);
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
	write(1, "minishell $> ", 13);
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
	tcsetattr(0, TCSANOW, &sh->old_tty);
	return (prepare_command(sh));
}
