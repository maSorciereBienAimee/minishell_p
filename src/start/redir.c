/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 09:47:56 by ssar              #+#    #+#             */
/*   Updated: 2021/06/11 09:34:34 by ssar             ###   ########.fr       */
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
/*

void	redir_cur(t_sh *sh, char *spl)
{
	int fd;
	t_actual	*temp;
	char *str;

	temp = sh->actu->next;
	fd = open(".redir", O_RDWR | O_CREAT | O_APPEND, 00664);
	if (fd == -1)
		ft_error(sh, strerror(errno), NULL, NULL);
	str = NULL;
	while (ft_comp(str, temp->str_arg[0]) != 0)
	{
		if (str != NULL)
			free(str);
		str = readline("> ");
		if (str == NULL)
			ft_error(sh, "Closed by EOF", NULL, NULL);
		if (ft_comp(str, temp->str_arg[0]) != 0)
		{
			write(fd, str, ft_len(str));
			write(fd, "\n", 1);
		}
	}
	close(fd);
	fd = open(".redir", O_RDWR | O_CREAT | O_APPEND, 00664);
	if (dup2(fd, 0) < 0)
		ft_error(sh, strerror(errno), NULL, NULL);
}


void	redir_cur(t_sh *sh, char *spl)
{
	int fd;
	int i;

	i = 0;
	fd = open(".redir", O_RDWR | O_CREAT | O_TRUNC, 00644);
	if (fd == -1)
		ft_error(sh, strerror(errno), NULL, NULL);
	while (sh->redir->arg->str[i])
	{
		write(fd, sh->redir->arg->str[i], ft_len(sh->redir->arg->str[i]));
		write(fd, "\n", 1);
		i++;
	}
	close(fd);
	fd = open(".redir", O_RDONLY, 00644);
	if (dup2(fd, 0) < 0)
		ft_error(sh, strerror(errno), NULL, NULL);
	sh->redir->arg = sh->redir->arg->next;
}
*/
void	redir_cur(t_sh *sh, char *spl)
{
	char	buf[10];
	int		status;
	pid_t	pid;
	int i;
	//t_arg_redir *temp;
	t_actual	*temp;

	temp = sh->actu->next;
	i = 0;
	pipe(sh->fd_redir);
	pid = fork();
	if (pid == -1)
		ft_error(sh, strerror(errno), NULL, NULL);
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
	//	sh->stock_for_pipe = sh->actu->next;
	//	sh->actu = sh->stock_for_pipe;
		sh->redir->arg = sh->redir->arg->next;
	}
	else
	{
	void	*ptr1;
	void	*ptr2;

	ptr1 = &(handler_sigquit);
	ptr2 = &(handler_sigint);
	signal(SIGQUIT, ptr1);
	signal(SIGINT, ptr2);
	if (sh->fd_redir[0])
		close(sh->fd_redir[0]);
	if (dup2(sh->fd_redir[1], 1) < 0)
		ft_error(sh, strerror(errno), NULL, NULL);
	close(sh->fd_redir[1]);
	int a = 0;
	while (sh->redir->arg->str[a])
	{
		write(1, sh->redir->arg->str[a], ft_len(sh->redir->arg->str[a]));
		write(1, "\n", 1);
		a++;
	}
	sh->ready = 0;
//	sh->fils_pid = pid;
//	g_my_sig.pid_suivant = pid;
	g_my_sig.exec_pid = pid;
	close(1);
	write(2, "redir wait\n", 11);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		sh->code = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
	{
		sh->code = WTERMSIG(status) + 128;
		if (WCOREDUMP(status))
			write(2, "Quit (core dumped)", 19);
	}
	g_my_sig.exec_pid = -2;
	my_exit(sh);


	}

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
		redir_cur(sh, spl);
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
