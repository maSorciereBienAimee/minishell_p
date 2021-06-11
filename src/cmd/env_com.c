/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_com.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 18:32:01 by ssar              #+#    #+#             */
/*   Updated: 2021/06/08 19:16:30 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

int	program_after(t_sh *sh, char **lst)
{
	int		i;
	pid_t	pid;

	i = 0;
	while (lst[i] && is_name_eq_value(lst[i]) == 1)
		i++;
	if (lst[i])
		return (i);
	return (-1);
}

void	fill_new_lst(t_sh *sh, char *new, char *old)
{
	int	j;
	int	len;

	len = ft_len(old);
	j = 0;
	new = (char *)malloc(sizeof(char) * (len + 1));
	if (!new)
		ft_error(sh, strerror(errno), NULL, NULL);
	while (old[j])
	{
		new[j] = old[j];
		j++;
	}
	new[j] = '\0';
}

char	**get_new_lst(t_sh *sh, char **lst, int i)
{	
	char	**new_lst;
	int		count;
	int		k;

	k = i;
	count = 0;
	while (lst[i])
	{
		i++;
		count++;
	}
	i = k;
	new_lst = (char **)malloc(sizeof(char *) * (count + 1));
	if (!new_lst)
		ft_error(sh, strerror(errno), NULL, NULL);
	k = 0;
	while (lst[i])
	{
		fill_new_lst(sh, new_lst[k], lst[i]);
		i++;
		k++;
	}
	new_lst[count] = 0;
	return (lst);
}

void	execute_with_new_env(t_sh *sh, char *prog, char **lst, int i)
{
	pid_t	pid;
	char	**new_lst;

	pid = fork();
	sh->ready = 0;
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		sh->fils_pid = -2;
		sh->test_exec = 0;
		launch_exec(sh, NULL, prog, &lst[i]);
	}
	else
	{
		ft_free_tab(lst);
		continue_parent(sh, pid);
	}
}

void	env_command(t_sh *sh, char *spl, char **lst)
{
	t_list_env	*temp;
	int			prog;

	temp = sh->var_env;
	if (sh->actu->arg_command == 1)
		print_env(sh);
	else
	{
		modify_env(sh, lst, 0);
		prog = program_after(sh, lst);
		if (prog != -1)
			execute_with_new_env(sh, lst[prog], lst, prog);
		else
			print_env(sh);
	}
	sh->var_env = temp;
	transform_env_tab(sh);
	sh->code = 0;
}
