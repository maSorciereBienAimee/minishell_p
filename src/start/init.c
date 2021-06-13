/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 16:07:29 by ssar              #+#    #+#             */
/*   Updated: 2021/06/11 18:03:26 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

t_gestion_sig	g_my_sig;

void	init_sh_bis(t_sh *sh)
{
	void	*ptr1;
	void	*ptr2;

	sh->result = (char *)malloc(sizeof(char) * 1);
	if (!sh->result)
		ft_error(sh, strerror(errno), NULL, NULL);
	sh->result[0] = '\0';
	sh->alloue[6] = 1;
	sh->fd_pipe[0] = 0;
	sh->fd_pipe[1] = 0;
	sh->code = 0;
	sh->fils_pid = -2;
	sh->test_exec = 0;
	sh->parent = 1;
	ptr1 = &(handler_sigquit);
	ptr2 = &(handler_sigint);
	signal(SIGQUIT, ptr1);
	signal(SIGINT, ptr2);
	g_my_sig.restart = 0;
	g_my_sig.fd_out = dup(1);
	if (g_my_sig.fd_out < 0)
		ft_error(sh, strerror(errno), NULL, NULL);
	sh->alloue[11] = 1;
	g_my_sig.pid_suivant = -2;
	g_my_sig.exec_pid = -2;
}

void	init_sh(t_sh *sh, char **tab_env)
{
	int	j;

	j = -1;
	while (++j < 13)
		sh->alloue[j] = 0;
	sh->path = (char *)malloc(sizeof(char) * 1);
	if (!sh->path)
		ft_error(sh, strerror(errno), NULL, NULL);
	sh->alloue[0] = 1;
	actual_path(sh);
	sh->command = (char *)malloc(sizeof(char) * 1);
	if (!sh->command)
		ft_error(sh, strerror(errno), NULL, NULL);
	sh->command[0] = '\0';
	sh->alloue[1] = 1;
	sh->spl = (char **)malloc(sizeof(char *) * 1);
	if (!sh->spl)
		ft_error(sh, strerror(errno), NULL, NULL);
	sh->spl[0] = 0;
	sh->alloue[2] = 1;
	init_variable(sh, tab_env);
	transform_env_tab(sh);
	init_sh_bis(sh);
	sh->fd_redir[0] = 0;
	sh->fd_redir[1] = 0;
}

void	increase_shlvl(t_sh *sh)
{
	t_list_env	*temp;
	int			shlvl;

	temp = sh->var_env;
	while (sh->var_env && ft_comp(sh->var_env->name, "SHLVL") != 0)
		sh->var_env = sh->var_env->next;
	if (sh->var_env != NULL)
	{
		shlvl = ft_atoi(sh->var_env->value);
		shlvl++;
		free(sh->var_env->value);
		sh->var_env->value = ft_itoa(shlvl);
		if (!sh->var_env->value)
			ft_error(sh, strerror(errno), NULL, NULL);
	}
	sh->var_env = temp;
}

void	init_origin(t_sh *sh, char **envp)
{
	sh->parent = 1;
	sh->save_stdout = dup(1);
	sh->exit = 0;
	sh->last_exit = 0;
	sh->fils_pid = -2;
	init_variable(sh, envp);
	sh->tab_env = (char **)malloc(sizeof(char *) * 1);
	if (!sh->tab_env)
		ft_error(sh, strerror(errno), NULL, NULL);
	sh->tab_env[0] = 0;
	sh->alloue[7] = 1;
	increase_shlvl(sh);
	transform_env_tab(sh);
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
