/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 10:56:31 by ssar              #+#    #+#             */
/*   Updated: 2021/06/12 15:04:52 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

t_gestion_sig	g_my_sig;

void	cmd_in_child(t_sh *sh, char *spl)
{
	char	**lst_arguments;

	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	sh->fils_pid = -2;
	g_my_sig.exec_pid = -2;
	lst_arguments = all_arg(sh);
	if (ft_comp(lst_arguments[0], "exit") == 0)
		exit_command(sh, lst_arguments, sh->actu);
	else if (ft_comp(lst_arguments[0], "pwd") == 0)
		pwd_command(sh, spl);
	else if (ft_comp(lst_arguments[0], "export") == 0)
		export_command(sh, spl, lst_arguments, sh->actu);
	else if (ft_comp(lst_arguments[0], "cd") == 0)
		cd_command(sh, spl, sh->actu, lst_arguments);
	else if (ft_comp(lst_arguments[0], "env") == 0)
		env_command(sh, spl, lst_arguments);
	else if (ft_comp(lst_arguments[0], "echo") == 0)
		echo_command(sh, spl, sh->stock_for_pipe, lst_arguments);
	else if (ft_comp(lst_arguments[0], "unset") == 0)
		unset_command(sh, spl, lst_arguments, sh->actu);
	else
		launch_exec(sh, spl, lst_arguments[0], lst_arguments);
	ft_free_tab(lst_arguments);
	my_exit(sh);
}

void	continue_parent(t_sh *sh, pid_t pid)
{
	int		status;
	void	*ptr1;
	void	*ptr2;

	ptr1 = &(handler_sigquit);
	ptr2 = &(handler_sigint);
	g_my_sig.exec_pid = pid;
	sh->test_exec = pid;
	signal(SIGQUIT, ptr1);
	signal(SIGINT, ptr2);
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

void	execute_cmd(t_sh *sh, char *spl)
{
	pid_t	pid;

	sh->test_exec = 0;
	pid = fork();
	sh->ready = 0;
	if (pid == 0)
		cmd_in_child(sh, spl);
	else
		continue_parent(sh, pid);
}
