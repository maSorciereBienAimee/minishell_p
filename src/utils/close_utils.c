/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 20:34:26 by ssar              #+#    #+#             */
/*   Updated: 2021/06/18 10:56:35 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

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

void	my_exit(t_sh *sh)
{
	int	status;

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
