/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 16:36:16 by ssar              #+#    #+#             */
/*   Updated: 2021/06/25 10:36:48 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

void	ft_error_cmd(t_sh *sh, char *str, char *cmd, char *pb)
{
	sh->code = 127;
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
	my_exit(sh, NULL);
}

void	ft_error(t_sh *sh, char *str, char *cmd, char *pb)
{
	char	*new;
	int		i;

	i = -1;
	sh->code = 1;
	new = (char *)malloc(sizeof(char) * (ft_len(str) + 2));
	if (!new)
		my_exit(sh, NULL);
	while (str[++i])
		new[i] = str[i];
	new[i] = '\n';
	new[++i] = '\0';
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
	write(2, new, ft_len(new));
	my_exit(sh, new);
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
