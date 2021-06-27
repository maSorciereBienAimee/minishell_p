/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_com.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 17:37:41 by ssar              #+#    #+#             */
/*   Updated: 2021/06/27 18:20:48 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

t_gestion_sig	g_my_sig;

int	arg_is_invalid(char *arg)
{
	int	i;

	i = 0;
	if (ft_in(arg[i], "0123456789-+") == 0)
		return (1);
	i++;
	while (arg[i])
	{
		if (arg[i] != '0'
			&& arg[i] != '1'
			&& arg[i] != '2'
			&& arg[i] != '3'
			&& arg[i] != '4'
			&& arg[i] != '5'
			&& arg[i] != '6'
			&& arg[i] != '7'
			&& arg[i] != '8'
			&& arg[i] != '9')
			return (1);
		i++;
	}
	return (0);
}

void	check_status_exit(t_sh *sh, int *i)
{
	if (*i >= 256)
	{
		while (*i >= 256)
			*i = *i - 256;
	}
	else if (*i < 0)
	{
		while (*i < 0)
			*i = 256 + *i;
	}
	sh->code = *i;
}

void	err_exit_numarg(char *cmd, char *pb)
{
	write(2, "minishell : ", 12);
	if (cmd != NULL)
	{
		write(2, cmd, ft_len(cmd));
		write(2, ": ", 2);
	}
	if (pb != NULL)
	{
		write(2, pb, ft_len(pb));
		write(2, ": ", 2);
	}
	write(2, "numeric argument required\n", 26);
}

void	quit_or_not(t_sh *sh, char **lst, int code)
{
	if (sh->parent == 1)
	{
		sh->last_exit = code;
		ft_free_tab(lst);
		my_free(sh);
		my_exit_final(sh);
	}
	sh->exit = 1;
}

void	exit_command(t_sh *sh, char **lst, t_actual *temp)
{
	int	i;
	int	a;

	a = temp->arg_command;
	if (a > 1 && arg_is_invalid(lst[1]) == 1)
	{
		sh->code = 2;
		sh->exit = 1;
		err_exit_numarg(lst[0], lst[1]);
		return ;
	}
	if (a >= 3)
	{
		ft_error(sh, "too many arguments", lst[0], NULL);
		sh->code = 1;
		return ;
	}
	if (a == 1)
		sh->code = sh->last_exit;
	if (a == 2)
	{
		i = ft_atoi(lst[1]);
		check_status_exit(sh, &i);
	}
	quit_or_not(sh, lst, sh->code);
}
