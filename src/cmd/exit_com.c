/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_com.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 17:37:41 by ssar              #+#    #+#             */
/*   Updated: 2021/06/08 19:19:59 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

t_gestion_sig	g_my_sig;

int	arg_is_invalid(char *arg)
{
	int	i;

	i = 0;
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

void	exit_command(t_sh *sh, char **lst, t_actual *temp)
{
	int	i;
	int	a;

	a = temp->arg_command;
	if (a > 1 && arg_is_invalid(lst[1]) == 1)
	{
		ft_error(sh, "numeric qrgument required", lst[0], lst[1]);
		sh->code = 128;
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
		sh->code = i;
	}
	sh->exit = 1;
}
