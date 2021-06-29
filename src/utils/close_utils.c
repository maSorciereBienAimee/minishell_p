/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 20:34:26 by ssar              #+#    #+#             */
/*   Updated: 2021/06/29 16:11:39 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

void	my_exit_final(t_sh *sh)
{
	if (sh->alloue[7] == 1)
		ft_free_tab(sh->tab_env);
	close(sh->save_stdout);
	write(2, "exit\n", 5);
	write_history(sh->history, sh->pwd_path);
	free_history(sh->history);
	free(sh->home_path);
	free(sh->pwd_path);
	exit(sh->last_exit);
}

void	wait_exit(t_sh *sh)
{
	int	status;

	close(1);
	close(0);
	waitpid(sh->fils_pid, &status, 0);
	if (WIFEXITED(status))
	{
		sh->code = WEXITSTATUS(status);
	}
	else if (WIFSIGNALED(status))
	{
		sh->code = WTERMSIG(status) + 128;
		if (WCOREDUMP(status))
			write(2, "Quit (core dumped)", 19);
	}
	else
		sh->code = 0;
	if (sh->parent == 1)
		return ;
	my_free(sh);
	exit(sh->code);
}

void	my_exit(t_sh *sh, char *word)
{
	int	status;

	if (word != NULL)
		free(word);
	if (sh->if_redir_cur == 0)
	{
		my_free(sh);
		exit(sh->code);
	}
	if (sh->fils_pid != -2)
		wait_exit(sh);
	if (sh->fils_pid == -2)
	{
		close(1);
		close(0);
		if (sh->parent == 1)
			return ;
		my_free(sh);
		exit(sh->code);
	}
}

void	suite_redir(t_sh *sh)
{
	sh->redir->arg = sh->stock_redir_arg;
	if (sh->redir->next != NULL)
	{
		sh->redir = sh->redir->next;
		sh->stock_redir_arg = sh->redir->arg;
	}
}

void	init_meta(t_actual *ptr)
{
	ptr->pipe = 0;
	ptr->append = 0;
	ptr->redir_cur = 0;
	ptr->redir_out = 0;
	ptr->redir_in = 0;
	ptr->no_suite = 0;
}
