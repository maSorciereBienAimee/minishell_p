/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_current.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 12:47:36 by ssar              #+#    #+#             */
/*   Updated: 2021/06/18 23:27:58 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

t_gestion_sig	g_my_sig;

void	ft_wait(t_sh *sh, pid_t pid)
{
	int	status;

	sh->ready = 0;
	close(1);
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
	if (sh->redir->arg->str != NULL)
	{
		while (sh->redir->arg->str[i])
		{
			write(1, sh->redir->arg->str[i], ft_len(sh->redir->arg->str[i]));
			write(1, "\n", 1);
			i++;
		}
	}
	ft_wait(sh, pid);
}

void	redir_cur(t_sh *sh, char *spl)
{
	char		buf[10];
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
