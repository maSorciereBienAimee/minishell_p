/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 11:15:01 by ssar              #+#    #+#             */
/*   Updated: 2021/06/08 22:38:00 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H
# include "minishell.h"

void		analyse_command(t_sh *sh, char *spl);
void		get_command(t_sh *sh);
void		actual_path(t_sh *sh);
void		init_sh(t_sh *sh, char **envp);
void		init_origin(t_sh *sh, char **envp);
void		init_variable(t_sh *sh, char **envp);
t_list_env	*create_new_env(t_sh *sh, char *envp);
void		get_value_env(t_sh *sh, t_list_env *ptr, char *envp, int i);
int			get_name_env(t_sh *sh, t_list_env *ptr, char *envp);
void		transform_env_tab(t_sh *sh);
void		exit_command(t_sh *sh, char **lst, t_actual *temp);
void		pwd_command(t_sh *sh, char *spl);
void		env_command(t_sh *sh, char *spl, char **lst);
void		cd_command(t_sh *sh, char *spl, t_actual *temp, char **lst);
void		unset_command(t_sh *sh, char *spl, char **lst, t_actual *temp);
void		export_command(t_sh *sh, char *spl, char **lst, t_actual *temp);
int			count_letters(t_sh *sh, char *spl, int *i);
t_actual	*get_arg_of_cmd(t_sh *sh, char *spl, int *i);
int			no_fork_exec(t_sh *sh, int j);

#endif
