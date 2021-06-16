/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 19:43:40 by ssar              #+#    #+#             */
/*   Updated: 2021/06/16 13:21:23 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

t_gestion_sig	g_my_sig;

void	set_new_parent(t_sh *sh, pid_t pid)
{
	void	*ptr1;
	void	*ptr2;

	ptr1 = &(handler_sigquit);
	ptr2 = &(handler_sigint);
	signal(SIGQUIT, ptr1);
	signal(SIGINT, ptr2);
	if (sh->fd_pipe[0])
		close(sh->fd_pipe[0]);
	if (dup2(sh->fd_pipe[1], 1) < 0)
		ft_error(sh, strerror(errno), NULL, NULL);
	close(sh->fd_pipe[1]);
	sh->ready = 0;
	sh->fils_pid = pid;
	g_my_sig.pid_suivant = pid;
}

void	aligne_redir_current(t_sh *sh, int redir)
{
	int		i;

	i = 0;
	while (i < redir)
	{
		sh->redir->arg = sh->redir->arg->next;
		i++;
	}
}

void	ft_pipe(t_sh *sh, char *spl, int redir)
{
	char	buf[10];
	int		status;
	pid_t	pid;

	pipe(sh->fd_pipe);
	pid = fork();
	if (pid == -1)
		ft_error(sh, strerror(errno), NULL, NULL);
	else if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		sh->fils_pid = -2;
		if (sh->fd_pipe[1])
			close(sh->fd_pipe[1]);
		if (dup2(sh->fd_pipe[0], 0) < 0)
			ft_error(sh, strerror(errno), NULL, NULL);
		close(sh->fd_pipe[0]);
		aligne_redir_current(sh, redir);	
		sh->stock_for_pipe = sh->actu->next;
		sh->actu = sh->stock_for_pipe;
		boucle_minishell(sh, spl);
	}
	else
		set_new_parent(sh, pid);
}

void	is_it_pipe(t_sh *sh, char *spl)
{
	int			stop;
	t_actual	*stock;
	int			redir;

	redir = 0;
	stop = 0;
	stock = sh->actu;
	while (stop == 0)
	{
		if (sh->actu->pipe == 1)
		{
			ft_pipe(sh, spl, redir);
			stop = 1;
		}
		if (sh->actu->redir_cur == 1)
			redir++;
		if (sh->actu->next == NULL)
			stop = 1;
		else
			sh->actu = sh->actu->next;
	}
	sh->actu = stock;
}
