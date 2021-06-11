/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 15:33:39 by ssar              #+#    #+#             */
/*   Updated: 2021/06/07 10:00:16 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

void	ft_swap(char **s1, char **s2)
{
	char	*s3;

	s3 = *s1;
	*s1 = *s2;
	*s2 = s3;
}

void	actual_path(t_sh *sh)
{
	sh->size_path = 1;
	getcwd(sh->path, sh->size_path);
	while (errno == ERANGE)
	{
		errno = 0;
		sh->size_path++;
		sh->path = my_realloc(sh, sh->path, sh->size_path);
		getcwd(sh->path, sh->size_path);
	}
}

int	is_al_num(char c)
{
	int	i;

	if ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z')
		|| (c >= 'a' && c <= 'z') || c == '_')
		return (1);
	return (0);
}

char	*get_lst_value_of(t_sh *sh, char *name)
{
	t_list_env	*temp;
	t_list_env	*temp2;

	temp = sh->var_env;
	while (sh->var_env->next != NULL && ft_comp(sh->var_env->name, name) != 0)
		sh->var_env = sh->var_env->next;
	if (sh->var_env->next == NULL && ft_comp(sh->var_env->name, name) != 0)
	{
		sh->var_env = temp;
		return (NULL);
	}
	temp2 = sh->var_env;
	sh->var_env = temp;
	return (temp2->value);
}
