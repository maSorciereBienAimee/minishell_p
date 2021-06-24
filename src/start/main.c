/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 11:10:56 by ssar              #+#    #+#             */
/*   Updated: 2021/06/24 18:26:09 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

t_gestion_sig	g_my_sig;

void	boucle_minishell(t_sh *sh, char *spl)
{
	int	status;

	sh->stop = 0;
	sh->ready = 0;
	sh->if_redir_cur = 1;
	is_it_pipe(sh, spl);
	while (sh->stop == 0)
		manage_redir(sh, spl);
	my_exit(sh);
}

void	run_child(t_sh *sh, int j)
{
	t_actual	*temp;

	g_my_sig.pid_suivant = -2;
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	sh->i = 0;
	sh->parent = 0;
	sh->fils_pid = -2;
	sh->end_cmd = 0;
	sh->actu = get_arg_of_cmd(sh, sh->spl[j], &sh->i);
	sh->alloue[10] = 1;
	while (sh->end_cmd == 0)
	{
		temp = get_arg_of_cmd(sh, sh->spl[j], &sh->i);
		lst_add_back_cmd(&sh->actu, temp);
	}
	sh->stock_actu = sh->actu;
	sh->stock_for_pipe = sh->actu;
	boucle_minishell(sh, sh->spl[j]);
}

void	run_parent(t_sh *sh, pid_t pid)
{
	int	status;

	sh->fils_pid = pid;
	g_my_sig.pid_suivant = pid;
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	{
		if (WEXITSTATUS(status))
			write(2, "\n", 2);
		sh->last_exit = WEXITSTATUS(status);
	}
	else if (WIFSIGNALED(status))
	{
		sh->last_exit = WTERMSIG(status) + 128;
	}
}

void	run_commande(t_sh *sh)
{
	int			j;
	int			pid;
	t_actual	*temp;
	int			a;

	if (sh->spl == NULL)
		return ;
	j = -1;
	while (sh->spl[++j] != 0)
	{
		a = no_fork_exec(sh, j);
		if (a == 0)
		{
			pid = fork();
			if (pid == -1)
				ft_error(sh, strerror(errno), NULL, NULL);
			else if (pid == 0)
				run_child(sh, j);
			else
				run_parent(sh, pid);
		}
		suite_redir(sh);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	t_sh	sh;
	int		a;
	char	*name_term;

	if (argc != 1)
	{
		write(2, "Wrong number of arguments\n", 26);
		exit(1);
	}
	name_term = getenv("TERM");
	init_origin(&sh, envp, name_term);
	if (sh.alloue[4] == 1)
		ft_free_list(&sh.var_env);
	sh.alloue[4] = 0;
	while (sh.exit == 0)
	{
		init_sh(&sh, sh.tab_env);
		a = get_command(&sh);
		if (g_my_sig.restart == 1)
			write(2, "\n", 1);
		if (g_my_sig.restart == 0 && a == 0)
			run_commande(&sh);
		my_free(&sh);
	}
	my_exit_final(&sh);
}
