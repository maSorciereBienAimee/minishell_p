/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 09:47:56 by ssar              #+#    #+#             */
/*   Updated: 2021/06/19 20:08:19 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

void	append(t_sh *sh, char *spl)
{
	int			fd_file;
	t_actual	*temp;

	temp = sh->actu->next;
	fd_file = open(temp->str_arg[0], O_CREAT | O_RDWR | O_APPEND, 00664);
	if (fd_file == -1)
		ft_error(sh, strerror(errno), temp->str_arg[0], NULL);
	if (dup2(fd_file, 1) < 0)
		ft_error(sh, strerror(errno), NULL, NULL);
}

void	redir_out(t_sh *sh, char *spl)
{
	int			fd_file;
	t_actual	*temp;

	temp = sh->actu->next;
	fd_file = open(temp->str_arg[0], O_CREAT | O_RDWR | O_TRUNC, 00664);
	if (fd_file == -1)
		ft_error(sh, strerror(errno), temp->str_arg[0], NULL);
	if (dup2(fd_file, 1) < 0)
		ft_error(sh, strerror(errno), NULL, NULL);
}

void	redir_in(t_sh *sh, char *spl)
{
	int			fd_file;
	t_actual	*temp;

	temp = sh->actu->next;
	fd_file = open(temp->str_arg[0], O_RDONLY, 00664);
	if (fd_file == -1)
		ft_error(sh, strerror(errno), temp->str_arg[0], NULL);
	if (dup2(fd_file, 0) < 0)
		ft_error(sh, strerror(errno), NULL, NULL);
}

int	manage_redir(t_sh *sh, char *spl)
{
	int	stop;

	if (sh->actu->redir_out == 1)
		redir_out(sh, spl);
	if (sh->actu->append == 1)
		append(sh, spl);
	if (sh->actu->redir_in == 1)
		redir_in(sh, spl);
	if (sh->actu->redir_cur == 1)
		redir_current(sh, spl);
	if (sh->actu->next == NULL || sh->actu->pipe == 1)
	{
		sh->ready = 1;
		sh->stop = 1;
	}
	if (sh->ready == 1)
	{
		sh->ready = 0;
		execute_cmd(sh, spl);
	}
	else
		sh->actu = sh->actu->next;
	return (0);
}
