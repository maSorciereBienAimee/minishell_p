/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_current_b.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 23:24:34 by ssar              #+#    #+#             */
/*   Updated: 2021/06/18 23:32:15 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

t_gestion_sig	g_my_sig;

int	ft_wait_b(t_sh *sh, int pid, t_actual *stock, char **lst)
{
	int	status;

	sh->ready = 0;
	close(sh->save_stdout);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		sh->code = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
	{
		sh->code = WTERMSIG(status) + 128;
		if (WCOREDUMP(status))
			write(2, "Quit (core dumped)", 19);
	}
	if (sh->if_redir_cur == 0)
	{
		my_free(sh);
		exit(sh->code);
	}
	my_free(sh);
	ft_free_lst_cmd(&stock);
	if (sh->alloue[7] == 1)
		ft_free_tab(sh->tab_env);
	exit(sh->code);
	return (2);
}

int	parent_redir_cur_b(t_sh *sh, int pid, t_actual *stock, char **lst)
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
	if (sh->redir->arg->str != NULL)
	{
		while (sh->redir->arg->str[i])
		{
			write(1, sh->redir->arg->str[i], ft_len(sh->redir->arg->str[i]));
			write(1, "\n", 1);
			i++;
		}
	}
	return (ft_wait_b(sh, pid, stock, lst));
}

int	redir_cur_b(t_sh *sh, char *spl, t_actual *stock, char **lst)
{
	char		buf[10];
	pid_t		pid;
	t_actual	*temp;

	temp = stock->next;
	pipe(sh->fd_redir);
	pid = fork();
	if (pid == -1)
		return (-1);
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
		sh->redir->arg = sh->redir->arg->next;
		return (1);
	}
	else
		return (parent_redir_cur_b(sh, pid, stock, lst));
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
