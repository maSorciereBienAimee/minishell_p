/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_current.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 12:47:36 by ssar              #+#    #+#             */
/*   Updated: 2021/06/19 22:10:33 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

t_gestion_sig	g_my_sig;

void	quit_child(t_sh *sh)
{
	close(1);
	my_free(sh);
	exit(0);
}

void	child_redir_cur(t_sh *sh, char *spl)
{
	int		i;

	i = 0;
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	sh->fils_pid = -2;
	if (sh->fd_redir[0])
		close(sh->fd_redir[0]);
	if (dup2(sh->fd_redir[1], 1) < 0)
	{
		ft_error(sh, strerror(errno), NULL, NULL);
		exit(1);
	}
	close(sh->fd_redir[1]);
	if (sh->redir->arg->str != NULL)
	{
		while (sh->redir->arg->str[i])
		{
			write(1, sh->redir->arg->str[i], ft_len(sh->redir->arg->str[i]));
			write(1, "\n", 1);
			i++;
		}
	}
	quit_child(sh);
}

void	parent_redir_cur(t_sh *sh, char *spl, int pid)
{
	int	status;

	if (sh->fd_redir[1])
		close(sh->fd_redir[1]);
	if (dup2(sh->fd_redir[0], 0) < 0)
	{
		g_my_sig.exec_pid = sh->fils_pid;
		ft_error(sh, strerror(errno), NULL, NULL);
	}
	close(sh->fd_redir[0]);
	if (sh->redir->arg->next != NULL)
		sh->redir->arg = sh->redir->arg->next;
	waitpid(pid, &status, 0);
	g_my_sig.exec_pid = sh->fils_pid;
}

void	redir_current(t_sh *sh, char *spl)
{
	pid_t		pid;
	t_actual	*temp;
	void		*ptr1;
	void		*ptr2;

	temp = sh->actu->next;
	pipe(sh->fd_redir);
	pid = fork();
	if (pid == -1)
		ft_error(sh, strerror(errno), NULL, NULL);
	else if (pid == 0)
		child_redir_cur(sh, spl);
	else
	{
		g_my_sig.exec_pid = pid;
		ptr1 = &(handler_sigquit);
		ptr2 = &(handler_sigint);
		signal(SIGQUIT, ptr1);
		signal(SIGINT, ptr2);
		parent_redir_cur(sh, spl, pid);
	}
}
