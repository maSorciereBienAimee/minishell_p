/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 16:14:32 by ssar              #+#    #+#             */
/*   Updated: 2021/06/29 14:31:18 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

int	get_name_env(t_sh *sh, t_list_env *ptr, char *envp)
{
	int	i;
	int	j;

	i = 0;
	j = -1;
	while (envp[i] && envp[i] != '=')
		i++;
	ptr->name = (char *)malloc(sizeof(char) * (i + 1));
	if (!ptr->name)
		ft_error(sh, strerror(errno), NULL, NULL);
	while (++j < i)
		ptr->name[j] = envp[j];
	ptr->name[i] = '\0';
	return (i);
}

void	get_value_env(t_sh *sh, t_list_env *ptr, char *envp, int i)
{
	int	j;
	int	k;
	int	l;

	l = i + 1;
	k = 0;
	j = -1;
	if (envp[i] == '\0')
		k = 0;
	else
	{
		while (envp[++i] != '\0')
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
	if (envp[i] == '=')
		ptr->equal = 1;
	else
		ptr->equal = 0;
	get_value_env(sh, ptr, envp, i);
	ptr->next = NULL;
	return (ptr);
}

void	get_origin_path(t_sh *sh, t_list_env *temp)
{
	t_list_env	*stock;
	int			stop;

	stop = 0;
	stock = temp;
	sh->home_path = NULL;
	sh->pwd_path = NULL;
	while (stop == 0)
	{
		if (ft_comp("HOME", stock->name) == 0)
		{
			sh->home_path = copy_char(sh, sh->home_path, stock->value);
			sh->alloue[13] = 1;
		}
		if (ft_comp("PWD", stock->name) == 0)
		{
			sh->pwd_path = copy_char(sh, sh->pwd_path, stock->value);
			sh->alloue[14] = 1;
		}
		if (stock->next != NULL)
			stock = stock->next;
		else
			stop = 1;
	}
}

void	init_variable(t_sh *sh, char **envp, int a)
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
	if (a == 1)
		get_origin_path(sh, sh->var_env);
}
