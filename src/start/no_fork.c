/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 19:58:24 by ssar              #+#    #+#             */
/*   Updated: 2021/06/08 20:36:37 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

int	free_no_fork(t_sh *sh, t_actual *temp, char **lst, int ret)
{
	dup2(sh->save_stdout, 1);
	ft_free_lst_cmd(&temp);
	if (ret == 1 && lst != NULL)
	{
		ft_free_tab(lst);
		sh->last_exit = sh->code;
	}
	return (ret);
}

int	exec_or_not_no_fork(t_sh *sh, t_actual *temp, char **lst, int j)
{
	if (ft_comp(temp->str_arg[0], "unset") == 0)
	{
		unset_command(sh, NULL, lst, temp);
		return (free_no_fork(sh, temp, lst, 1));
	}
	if (ft_comp(temp->str_arg[0], "cd") == 0)
	{
		cd_command(sh, sh->spl[j], temp, lst);
		return (free_no_fork(sh, temp, lst, 1));
	}
	if (ft_comp(temp->str_arg[0], "exit") == 0)
	{
		exit_command(sh, lst, temp);
		return (free_no_fork(sh, temp, lst, 1));
	}
	if (ft_comp(temp->str_arg[0], "export") == 0 && temp->arg_command > 1)
	{
		export_command(sh, NULL, lst, temp);
		return (free_no_fork(sh, temp, lst, 1));
	}
	dup2(sh->save_stdout, 1);
	ft_free_tab(lst);
	ft_free_lst_cmd(&temp);
	return (0);
}

int	no_fork_exec(t_sh *sh, int j)
{
	t_actual	*temp;
	t_actual	*add;
	t_actual	*stock;
	int			ia[2];
	char		**lst;

	ia[0] = 0;
	sh->end_cmd = 0;
	temp = get_arg_of_cmd(sh, sh->spl[j], &ia[0]);
	while (sh->end_cmd == 0)
	{
		add = get_arg_of_cmd(sh, sh->spl[j], &ia[0]);
		lst_add_back_cmd(&temp, add);
	}
	sh->end_cmd = 0;
	stock = temp;
	ia[1] = manage_redir_b(sh, sh->spl[j], temp);
	if (ia[1] != 1)
		return (free_no_fork(sh, temp, NULL, ia[1]));
	temp = stock;
	lst = all_arg_b(sh, temp);
	temp = stock;
	return (exec_or_not_no_fork(sh, temp, lst, j));
}
