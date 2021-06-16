/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_current.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 12:47:36 by ssar              #+#    #+#             */
/*   Updated: 2021/06/16 13:23:06 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

t_gestion_sig	g_my_sig;

int	ft_wait_b(t_sh *sh, int pid)
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
	return (1);
}

int	parent_redir_cur_b(t_sh *sh, int pid)
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
		return (-1);
	close(sh->fd_redir[1]);
	while (sh->redir->arg->str[i])
	{
		write(1, sh->redir->arg->str[i], ft_len(sh->redir->arg->str[i]));
		write(1, "\n", 1);
		i++;
	}
	sh->ready = 0;
	close(sh->save_stdout);
	return (ft_wait_b(sh, pid));
}

int	redir_cur_b(t_sh *sh, char *spl, t_actual *stock)
{
	char		buf[10];
	int			status;
	pid_t		pid;
	t_actual	*temp;

	temp = stock->next;
	pipe(sh->fd_redir);
	pid = fork();
	if (pid == -1)
		return (-1);
	else if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		sh->fils_pid = -2;
		if (sh->fd_redir[1])
			close(sh->fd_redir[1]);
		if (dup2(sh->fd_redir[0], 0) < 0)
			ft_error(sh, strerror(errno), NULL, NULL);
		close(sh->fd_redir[0]);
		sh->redir->arg = sh->redir->arg->next;
		return (1);
	}
	else
		return (parent_redir_cur_b(sh, pid));
}

void	ft_wait(t_sh *sh, pid_t pid, pid_t stock)
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
	sh->fils_pid = stock;
	my_exit(sh);
}

void	parent_redir_cur(t_sh *sh, int pid)
{
	void	*ptr1;
	void	*ptr2;
	int		i;
	pid_t stock;

	stock = sh->fils_pid;
	sh->fils_pid = pid;
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
	ft_wait(sh, pid, stock);
}
