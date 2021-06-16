/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 09:47:56 by ssar              #+#    #+#             */
/*   Updated: 2021/06/16 11:32:33 by ssar             ###   ########.fr       */
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

void	redir_cur(t_sh *sh, char *spl)
{
	char		buf[10];
	int			status;
	pid_t		pid;
	t_actual	*temp;

	temp = sh->actu->next;
	pipe(sh->fd_redir);
	pid = fork();
	if (pid == -1)
		ft_error(sh, strerror(errno), NULL, NULL);
	else if (pid == 0)
	{
		sh->if_redir_cur = 0;
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		sh->fils_pid = -2;
		if (sh->fd_redir[1])
			close(sh->fd_redir[1]);
		if (dup2(sh->fd_redir[0], 0) < 0)
			ft_error(sh, strerror(errno), NULL, NULL);
		close(sh->fd_redir[0]);
		if (sh->redir->arg->next != NULL)
			sh->redir->arg = sh->redir->arg->next;
	}
	else
		parent_redir_cur(sh, pid);
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

void	redir_current(t_sh *sh, char *spl)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == -1)
		ft_error(sh, strerror(errno), NULL, NULL);
	else if (pid == 0)
		redir_cur(sh, spl);
	else
	{
		waitpid(pid, &status, 0);
		my_exit(sh);
	//	exit(sh->code);
	}
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
