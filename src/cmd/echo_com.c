/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_com.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 16:06:02 by ssar              #+#    #+#             */
/*   Updated: 2021/06/25 22:22:53 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

int	is_n_option(char *arg)
{
	int	i;

	if (arg[0] != '-')
		return (0);
	i = 1;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	echo_command(t_sh *sh, char *spl, t_actual *actu, char **arg)
{
	int	i;
	int	new_line;

	new_line = 1;
	i = 1;
	if (arg[1] && is_n_option(arg[1]) == 1)
	{
		new_line = 2;
		i = 2;
		while (arg[i] && is_n_option(arg[i]) == 1)
			i++;
	}
	while (arg[i] && arg[i + 1] != 0)
	{
		write(1, arg[i], ft_len(arg[i]));
		write(1, " ", 1);
		i++;
	}
	if (arg[i])
		write(1, arg[i], ft_len(arg[i]));
	if (new_line == 1)
		write(1, "\n", 1);
	sh->code = 0;
}
