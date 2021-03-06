/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 16:07:29 by ssar              #+#    #+#             */
/*   Updated: 2021/06/29 14:14:40 by ssar             ###   ########.fr       */
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
	while (++j < 15)
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
	init_variable(sh, tab_env, 0);
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

void	init_term(t_sh *sh, char *name)
{
	int	ret;
	int	j;

	j = -1;
	while (++j < 15)
		sh->alloue[j] = 0;
	if (name == NULL)
	{
		ft_error(sh, "'TERM' not set", NULL, NULL);
		exit(1);
	}
	ret = tgetent(NULL, name);
	if (ret < 1)
	{
		ft_error(sh, "Can't access to the termcap database", NULL, NULL);
		exit(1);
	}
	sh->tty_col = tgetnum("co");
	sh->tty_row = tgetnum("li");
}

void	init_origin(t_sh *sh, char **envp, char *name)
{
	init_term(sh, name);
	sh->history = build_history(1);
	if (sh->history == NULL)
	{
		ft_putstr_fd("Error allocation failed\n", 2);
		exit(EXIT_FAILURE);
	}
	sh->init_cursor_r = 0;
	sh->init_cursor_c = 0;
	sh->parent = 1;
	sh->if_redir_cur = 1;
	sh->in_read = 0;
	sh->save_stdout = dup(1);
	sh->exit = 0;
	sh->last_exit = 0;
	sh->fils_pid = -2;
	init_variable(sh, envp, 1);
	sh->tab_env = (char **)malloc(sizeof(char *) * 1);
	if (!sh->tab_env)
		ft_error(sh, strerror(errno), NULL, NULL);
	sh->tab_env[0] = 0;
	sh->alloue[7] = 1;
	increase_shlvl(sh);
	transform_env_tab(sh);
}
