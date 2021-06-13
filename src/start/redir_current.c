/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_current.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 12:47:36 by ssar              #+#    #+#             */
/*   Updated: 2021/06/12 12:50:14 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

t_gestion_sig	g_my_sig;

void	ft_wait(t_sh *sh, int pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		sh->code = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
	{
		sh->code = WTERMSIG(status) + 128;
		if (WCOREDUMP(status))
			write(2, "Quit (core dumped)", 19);
	}
	my_exit(sh);
}

void	parent_redir_cur(t_sh *sh, int pid)
{
	void	*ptr1;
	void	*ptr2;
	int		i;

	i = 0;
	g_my_sig.exec_pid = pid;
	ptr1 = &(handler_sigquit);
	ptr2 = &(handler_sigint);
	signal(SIGQUIT, ptr1);
	signal(SIGINT, ptr2);
	if (sh->fd_redir[0])
		close(sh->fd_redir[0]);
	if (dup2(sh->fd_redir[1], 1) < 0)
		ft_error(sh, strerror(errno), NULL, NULL);
	close(sh->fd_redir[1]);
	while (sh->redir->arg->str[i])
	{
		write(1, sh->redir->arg->str[i], ft_len(sh->redir->arg->str[i]));
		write(1, "\n", 1);
		i++;
	}
	sh->ready = 0;
	close(1);
	ft_wait(sh, pid);
}
