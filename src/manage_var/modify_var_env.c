/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_var_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 16:50:44 by ssar              #+#    #+#             */
/*   Updated: 2021/06/08 17:09:45 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

int	replace_if_existe(t_sh *sh, char *name, char *value)
{
	while (sh->var_env && ft_comp(sh->var_env->name, name) != 0)
		sh->var_env = sh->var_env->next;
	if (sh->var_env != NULL)
	{
		sh->var_env->value = copy_char(sh, sh->var_env->value, value);
		return (1);
	}
	return (0);
}

int	verify_name(t_sh *sh, char *name, char *group, char *cmd)
{
	int	i;

	if (!(name[0] >= 'A' && name[0] <= 'Z')
		&& !(name[0] >= 'a' && name[0] <= 'z')
		&& name[0] != '_')
	{
		ft_error(sh, "invalid name", cmd, group);
		return (-1);
	}
	i = 1;
	while (name[i])
	{
		if (!(name[0] >= 'A' && name[0] <= 'Z')
			&& !(name[0] >= 'a' && name[0] <= 'z')
			&& !(name[0] >= '0' && name[0] <= '9')
			&& name[0] != '_')
		{
			ft_error(sh, "invalid name", cmd, group);
			return (-1);
		}
		i++;
	}
	return (1);
}

void	boucle_modif(t_sh *sh, char **lst, int i, int exp)
{
	char		*name;
	char		*value;
	t_list_env	*stock;
	t_list_env	*new;

	stock = sh->var_env;
	name = get_name(sh, lst[i]);
	if (exp == 1)
	{
		if (verify_name(sh, name, lst[i], lst[0]) == -1)
		{
			free(name);
			return ;
		}
	}
	value = get_value(sh, lst[i]);
	if (replace_if_existe(sh, name, value) == 0)
	{
		sh->var_env = stock;
		new = create_new_env(sh, lst[i]);
		lst_add_back(&sh->var_env, new);
	}
	free(name);
	free(value);
}

void	modify_env(t_sh *sh, char **lst, int exp)
{
	t_list_env	*temp;
	t_list_env	*new;
	int			i;

	temp = sh->var_env;
	i = 1;
	while (lst[i] && is_name_eq_value(lst[i]) == 1)
	{
		sh->var_env = temp;
		boucle_modif(sh, lst, i, exp);
		i++;
	}
	sh->var_env = temp;
}
