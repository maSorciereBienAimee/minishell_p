/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 16:14:32 by ssar              #+#    #+#             */
/*   Updated: 2021/06/08 16:26:25 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

int	get_name_env(t_sh *sh, t_list_env *ptr, char *envp)
{
	int	i;
	int	j;

	i = 0;
	j = -1;
	while (envp[i] != '=')
		i++;
	ptr->name = (char *)malloc(sizeof(char) * (i + 1));
	if (!ptr->name)
		ft_error(sh, strerror(errno), NULL, NULL);
	while (++j < i)
		ptr->name[j] = envp[j];
	ptr->name[i] = '\0';
	i++;
	return (i);
}

void	get_value_env(t_sh *sh, t_list_env *ptr, char *envp, int i)
{
	int	j;
	int	k;
	int	l;

	l = i;
	k = 0;
	j = -1;
	while (envp[i] != '\0')
	{
		i++;
		k++;
	}
	ptr->value = (char *)malloc(sizeof(char) * (k + 1));
	if (!ptr->value)
		ft_error(sh, strerror(errno), NULL, NULL);
	while (++j < k)
	{
		ptr->value[j] = envp[l];
		l++;
	}
	ptr->value[k] = '\0';
}

t_list_env	*create_new_env(t_sh *sh, char *envp)
{
	t_list_env	*ptr;
	int			i;
	int			shlvl;

	ptr = (t_list_env *)malloc(sizeof(t_list_env));
	if (!ptr)
		ft_error(sh, strerror(errno), NULL, NULL);
	i = get_name_env(sh, ptr, envp);
	get_value_env(sh, ptr, envp, i);
	ptr->next = NULL;
	return (ptr);
}

void	init_variable(t_sh *sh, char **envp)
{
	int			i;
	t_list_env	*temp;

	sh->var_env = create_new_env(sh, envp[0]);
	sh->alloue[4] = 1;
	i = 1;
	while (envp[i] != 0)
	{
		temp = create_new_env(sh, envp[i]);
		lst_add_back(&sh->var_env, temp);
		i++;
	}
}
