/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_com.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 19:03:23 by ssar              #+#    #+#             */
/*   Updated: 2021/06/29 15:52:46 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

void	modify_newpwd(t_sh *sh)
{
	t_list_env	*temp;

	actual_path(sh);
	temp = sh->var_env;
	while (sh->var_env && ft_comp(sh->var_env->name, "PWD") != 0)
		sh->var_env = sh->var_env->next;
	if (sh->var_env != NULL)
	{
		sh->var_env->equal = 1;
		sh->var_env->value = copy_char(sh, sh->var_env->value, sh->path);
	}
	sh->var_env = temp;
	transform_env_tab(sh);
}

void	modifie_oldpwd(t_sh *sh)
{
	t_list_env	*temp;
	char		*path;

	temp = sh->var_env;
	path = get_lst_value_of(sh, "PWD");
	while (sh->var_env && ft_comp(sh->var_env->name, "OLDPWD") != 0)
		sh->var_env = sh->var_env->next;
	if (path == NULL)
	{
		sh->var_env->equal = 0;
		sh->var_env->value = copy_char(sh, sh->var_env->value, "");
	}
	else if (sh->var_env != NULL)
	{
		sh->var_env->equal = 1;
		sh->var_env->value = copy_char(sh, sh->var_env->value, sh->path);
	}
	sh->var_env = temp;
	modify_newpwd(sh);
}

int	is_home_cd(t_sh *sh, t_actual *temp, char **lst, char **ptr)
{
	if (temp->arg_command == 1)
	{
		*ptr = get_lst_value_of(sh, "HOME");
		if (*ptr == NULL)
		{
			ft_error(sh, "HOME not defined", "cd", NULL);
			return (-1);
		}
	}
	else if (ft_comp(lst[1], "~") == 0)
	{
		if (chdir((const char *)sh->home_path) < 0)
			return (-2);
		return (1);
	}
	return (0);
}

int	set_var(t_sh *sh, t_actual *temp, char **lst, char **ptr)
{
	int	a;

	a = is_home_cd(sh, temp, lst, ptr);
	if (a != 0)
		return (a);
	else if (ft_comp(lst[1], "-") == 0)
	{
		*ptr = get_lst_value_of(sh, "OLDPWD");
		if (*ptr == NULL)
		{
			ft_error(sh, "OLDPWD not defined", "cd", NULL);
			return (-1);
		}
	}
	if (*ptr != NULL)
	{
		if (chdir((const char *)*ptr) < 0)
			return (-2);
		return (1);
	}
	return (0);
}

void	cd_command(t_sh *sh, char *spl, t_actual *temp, char **lst)
{
	int		a;
	char	*ptr;

	ptr = NULL;
	if (temp->arg_command > 2)
	{
		ft_error(sh, "too many arguments", "cd", NULL);
		return ;
	}
	a = set_var(sh, temp, lst, &ptr);
	if (a < 0)
	{
		if (a == -2)
			ft_error(sh, strerror(errno), "cd", NULL);
		return ;
	}
	else if (a == 0)
	{
		if (chdir((const char *)lst[1]) < 0)
		{
			ft_error(sh, strerror(errno), "cd", lst[1]);
			return ;
		}
	}
	modifie_oldpwd(sh);
}
