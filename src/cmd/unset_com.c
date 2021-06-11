/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_com.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 11:56:49 by ssar              #+#    #+#             */
/*   Updated: 2021/06/08 19:48:51 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

t_list_env	*remov_env(t_sh *sh, t_list_env **p, t_list_env **a, t_list_env **r)
{
	t_list_env	*next;

	next = (*a)->next;
	free((*a)->name);
	free((*a)->value);
	free((*a));
	if (*p != NULL)
		(*p)->next = next;
	if (*p == NULL)
		(*r) = next;
	return (*r);
}

t_list_env	*boucle_unset(t_sh *sh, char **lst, int i, t_list_env **tmp_env)
{
	t_list_env	*previous;

	previous = NULL;
	while (sh->var_env && ft_comp(lst[i], sh->var_env->name) != 0)
	{
		previous = sh->var_env;
		sh->var_env = sh->var_env->next;
	}
	if (sh->var_env != NULL)
		*tmp_env = remov_env(sh, &previous, &sh->var_env, tmp_env);
	return (*tmp_env);
}

void	unset_command(t_sh *sh, char *spl, char **lst, t_actual *actu)
{
	t_list_env	*tmp_env;
	int			i;

	tmp_env = sh->var_env;
	if (actu->arg_command <= 1)
		return ;
	i = 1;
	while (lst[i] != 0)
	{
		sh->var_env = tmp_env;
		if (verify_name(sh, lst[i], lst[i], lst[0]) == -1)
		{
			i++;
			sh->code = 1;
			continue ;
		}
		else
		{
			tmp_env = boucle_unset(sh, lst, i, &tmp_env);
			i++;
		}
	}
	sh->var_env = tmp_env;
	transform_env_tab(sh);
}
