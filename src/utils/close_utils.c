/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 20:34:26 by ssar              #+#    #+#             */
/*   Updated: 2021/06/11 09:29:17 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

void	wait_exit(t_sh *sh)
{
	int	status;

	close(1);
	close(0);
	write(2, "wait end\n",9 );
	waitpid(sh->fils_pid, &status, 0);
	if (WIFEXITED(status))
		sh->code = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
	{
		sh->code = WTERMSIG(status) + 128;
		if (WCOREDUMP(status))
			write(2, "Quit (core dumped)", 19);
	}
	if (sh->parent == 1)
		return ;
	my_free(sh);
	exit(sh->code);
}

void	my_exit(t_sh *sh)
{
	int	status;

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
