/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_current_b.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 23:24:34 by ssar              #+#    #+#             */
/*   Updated: 2021/06/19 22:10:06 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

t_gestion_sig	g_my_sig;

void	quit_ch(t_sh *sh, t_actual *stock)
{
	close(1);
	my_free(sh);
	if (sh->alloue[7] == 1)
		ft_free_tab(sh->tab_env);
	ft_free_lst_cmd(&stock);
	exit(0);
}

void	child_redir_cur_b(t_sh *sh, char *spl, t_actual *actu, t_actual *stock)
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
	quit_ch(sh, stock);
}

int	parent_redir_cur_b(t_sh *sh, char *spl, int pid)
{
	int	status;

	if (sh->fd_redir[1])
		close(sh->fd_redir[1]);
	if (dup2(sh->fd_redir[0], 0) < 0)
	{
		g_my_sig.exec_pid = sh->fils_pid;
		ft_error(sh, strerror(errno), NULL, NULL);
		return (-1);
	}
	close(sh->fd_redir[0]);
	if (sh->redir->arg->next != NULL)
		sh->redir->arg = sh->redir->arg->next;
	waitpid(pid, &status, 0);
	g_my_sig.exec_pid = sh->fils_pid;
	return (1);
}

int	redir_current_b(t_sh *sh, char *spl, t_actual *actu, t_actual *stock)
{
	pid_t		pid;
	t_actual	*temp;
	void		*ptr1;
	void		*ptr2;

	temp = actu->next;
	pipe(sh->fd_redir);
	pid = fork();
	if (pid == -1)
	{
		ft_error(sh, strerror(errno), NULL, NULL);
		return (-1);
	}
	else if (pid == 0)
		child_redir_cur_b(sh, spl, actu, stock);
	else
	{
		g_my_sig.exec_pid = pid;
		ptr1 = &(handler_sigquit);
		ptr2 = &(handler_sigint);
		signal(SIGQUIT, ptr1);
		signal(SIGINT, ptr2);
		return (parent_redir_cur_b(sh, spl, pid));
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
