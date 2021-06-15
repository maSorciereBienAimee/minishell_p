/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_b.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 09:47:56 by ssar              #+#    #+#             */
/*   Updated: 2021/06/15 22:25:45 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

int	append_b(t_sh *sh, char *spl, t_actual *stock)
{
	int			fd_file;
	t_actual	*temp;

	temp = stock->next;
	fd_file = open(temp->str_arg[0], O_CREAT | O_RDWR | O_APPEND, 00664);
	if (fd_file == -1)
	{		
		ft_error(sh, strerror(errno), temp->str_arg[0], NULL);
		return (-1);
	}
	if (dup2(fd_file, 1) < 0)
	{		
		ft_error(sh, strerror(errno), NULL, NULL);
		return (-1);
	}
	return (1);
}

int	redir_out_b(t_sh *sh, char *spl, t_actual *stock)
{
	int			fd_file;
	t_actual	*temp;

	temp = stock->next;
	fd_file = open(temp->str_arg[0], O_CREAT | O_RDWR | O_TRUNC, 00664);
	if (fd_file == -1)
	{		
		ft_error(sh, strerror(errno), temp->str_arg[0], NULL);
		return (-1);
	}
	if (dup2(fd_file, 1) < 0)
	{		
		ft_error(sh, strerror(errno), NULL, NULL);
		return (-1);
	}
	return (1);
}

int	redir_in_b(t_sh *sh, char *spl, t_actual *stock)
{
	int			fd_file;
	t_actual	*temp;

	temp = stock->next;
	fd_file = open(temp->str_arg[0], O_RDONLY, 00664);
	if (fd_file == -1)
	{		
		ft_error(sh, strerror(errno), temp->str_arg[0], NULL);
		return (-1);
	}
	if (dup2(fd_file, 0) < 0)
	{		
		ft_error(sh, strerror(errno), NULL, NULL);
		return (-1);
	}
	return (1);
}

int	which_redir(t_sh *sh, char *spl, t_actual *temp)
{
	if (temp->pipe == 1)
		return (0);
	if (temp->redir_cur == 1)
	{
		if (redir_cur_b(sh, spl, temp) == -1)
			return (-1);
	}
	if (temp->redir_out == 1)
	{
		if (redir_out_b(sh, spl, temp) == -1)
			return (-1);
	}
	if (temp->append == 1)
	{
		if (append_b(sh, spl, temp) == -1)
			return (-1);
	}
	if (temp->redir_in == 1)
	{
		if (redir_in_b(sh, spl, temp) == -1)
			return (-1);
	}
	return (1);
}

int	is_pipe(t_sh *sh, t_actual *temp)
{
	int			stop;
	t_actual	**stock;

	stop = 0;
	stock = &temp;
	while (stop == 0)
	{
		if (temp->pipe == 1)
		{
			temp = *stock;
			return (1);
		}
		if (temp->next == NULL)
				stop = 1;
		else
			temp = temp->next;
	}
	temp = *stock;
	return (0);
}

int	manage_redir_b(t_sh *sh, char *spl, t_actual *temp)
{
	int	stop;
	int	a;

	stop = 0;
	if (is_pipe(sh, temp) == 1)
		return (0);
	while (stop == 0)
	{
		a = which_redir(sh, spl, temp);
		if (a == -1 || a == 0)
			return (a);
		if (temp->next == NULL)
			stop = 1;
		else
			temp = temp->next;
	}
	sh->redir->arg = sh->stock_redir_arg;
	return (1);
}
