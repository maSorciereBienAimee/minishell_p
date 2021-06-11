/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 16:36:16 by ssar              #+#    #+#             */
/*   Updated: 2021/06/07 10:28:24 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

void	ft_error(t_sh *sh, char *str, char *cmd, char *pb)
{
	sh->code = 1;
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
	write(2, str, ft_len(str));
	write(2, "\n", 1);
	my_exit(sh);
}

void	print_error_too_arg(t_sh *sh, char *str, char **lst)
{
	int	i;

	i = 0;
	write(2, "minishell: ", 11);
	write(2, lst[0], ft_len(lst[0]));
	write(2, ": ", 2);
	write(2, &str[i], ft_len(str));
}

void	print_error_inv_arg(t_sh *sh, char *str, char **lst)
{
	int	i;

	i = 0;
	write(2, "minishell: ", 11);
	write(2, lst[0], ft_len(lst[0]));
	write(2, ": ", 2);
	write(2, lst[1], ft_len(lst[1]));
	write(2, " : ", 3);
	write(2, &str[i], ft_len(str));
}
