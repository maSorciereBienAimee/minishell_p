/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_com.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 12:07:04 by ssar              #+#    #+#             */
/*   Updated: 2021/06/22 16:40:51 by nayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

int	check_nb(char *str)
{
	int j;

	j = 0;
	if (str[0] == '-')
		return (-1);
	while (str[j])
	{
		if (ft_in(str[j], "0123456789") == 0)
		{
			write(2, "minishell: history: ", 20);
			write(2, str, ft_len(str));
			write(2, " : invalid number\n", 18);
			return (-1);
		}
		j++;
	}
	return (1);
}

void	delete_row(t_sh *sh, char **lst, int *i)
{
	//while	(check_nb(lst[*i]) == 1)
	//{
	
//	}
}

void	history_command(t_sh *sh, char **lst_arg, t_actual *actu)
{
	int i;

	i = 1;
	if (lst_arg[1] == NULL)
		return (print_history(sh->history));
	while (lst_arg[i])
	{
		//if (ft_comp(lst_arg[i], "-a") == 0)
		if (ft_comp(lst_arg[i], "-c") == 0)
			return (clean_history(sh->history));
		if (ft_comp(lst_arg[i], "-d") == 0)
			return (delete_row(sh, lst_arg, &i));
	//	else if (ft_comp(lst_arg[i], "-r") == 0)
	//	else if (ft_comp(lst_arg[i], "-w") == 0)
		else
		{
			ft_error(sh, "invalid option", "history", lst_arg[i]);
			return ;
		}
		i++;
	}
}
