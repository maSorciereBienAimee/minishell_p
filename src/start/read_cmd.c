/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 11:33:36 by ssar              #+#    #+#             */
/*   Updated: 2021/06/12 15:02:00 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

t_gestion_sig	g_my_sig;

int	check_touche(t_sh*sh, char *b, int *j, int *i)
{
	int	k;

	k = 0;
	while (k < 4)
	{
		if (b[k] == EOF || b[k] == '\0')
			return (0);
		if (b[k] == '\n')
			return (1);
		if (b[k] != 127 && b[k] >= 32)
		{
			sh->command = stock_tab(sh, sh->command, *i);
			sh->command[*j] = b[k];
			sh->command[*i - 1] = '\0';
			(*i)++;
			(*j)++;
		}
		else
			printf("fleche\n");
		k++;
	}
	return (0);
}

int	read_quit(t_sh *sh, int a, char *buff)
{
	if (a < 0)
	{
		sh->alloue[11] = 0;
		sh->last_exit = 130;
		g_my_sig.restart = 1;
		return (-1);
	}
	if (a == 0)
	{
		if (buff[0] == 0)
		{
			my_free(sh);
			if (sh->alloue[7] == 1)
				ft_free_tab(sh->tab_env);
			sh->alloue[7] = 0;
			close(sh->save_stdout);
			exit(sh->last_exit);
		}
	}
	return (1);
}

void	get_command(t_sh *sh)
{
	int		i;
	int		j;
	int		stop;
	int		a;
	char	buff[4];

	i = -1;
	j = 0;
	stop = 0;
	write(1, "minishell $> ", 13);
	while (++i < 4)
		buff[i] = 0;
	i = 2;
	while (stop != 1)
	{
		a = read(g_my_sig.fd_out, &buff, 4);
		if (read_quit(sh, a, buff) == -1)
			return ;
		stop = check_touche(sh, buff, &j, &i);
		a = -1;
		while (++a < 4)
			buff[a] = 0;
	}
	sh->spl = ft_split_commande(sh, sh->command, ';');
	get_redir_cur(sh);
}
