/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_com.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 19:03:23 by ssar              #+#    #+#             */
/*   Updated: 2021/06/08 19:28:35 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

int	skip_until_path(char *spl)
{
	int	i;

	i = 0;
	while (ft_in(spl[i], " \t") == 1)
		i++;
	while (ft_in(spl[i], " \t") != 1)
		i++;
	while (ft_in(spl[i], " \t") == 1)
		i++;
	return (i);
}

char	*check_path(t_sh *sh, char *spl)
{
	char	*str;
	int		i;
	int		j;
	int		k;

	k = -1;
	j = 0;
	i = skip_until_path(spl);
	while (ft_in(spl[i], " \t") != 1 && spl[i] != '\0')
	{
		j++;
		i++;
	}
	i = i - (j + 1);
	str = (char *)malloc(sizeof(char) * j + 1);
	if (!str)
		ft_error(sh, strerror(errno), NULL, NULL);
	while (++k < j)
		str[k] = spl[++i];
	str[j] = '\0';
	return (str);
}

void	modifie_oldpwd(t_sh *sh)
{
	t_list_env	*temp;

	temp = sh->var_env;
	while (sh->var_env && ft_comp(sh->var_env->name, "OLDPWD") != 0)
		sh->var_env = sh->var_env->next;
	if (sh->var_env != NULL)
		sh->var_env->value = copy_char(sh, sh->var_env->value, sh->path);
	actual_path(sh);
	sh->var_env = temp;
	temp = sh->var_env;
	while (sh->var_env && ft_comp(sh->var_env->name, "PWD") != 0)
		sh->var_env = sh->var_env->next;
	if (sh->var_env != NULL)
		sh->var_env->value = copy_char(sh, sh->var_env->value, sh->path);
	sh->var_env = temp;
	transform_env_tab(sh);
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
	if (ft_comp(lst[1], "-") == 0)
		ptr = get_lst_value_of(sh, "OLDPWD");
	else if (ft_comp(lst[1], "~") == 0)
		ptr = get_lst_value_of(sh, "HOME");
	if (ptr != NULL)
		a = chdir((const char *)ptr);
	else
		a = chdir((const char *)lst[1]);
	if (a < 0)
		ft_error(sh, strerror(errno), "cd", lst[1]);
	modifie_oldpwd(sh);
}
