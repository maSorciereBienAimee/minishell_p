/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_in_tab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 11:22:39 by ssar              #+#    #+#             */
/*   Updated: 2021/06/08 16:35:45 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

void	fill_tab_value(t_sh *sh, int i)
{
	int	len;
	int	j;
	int	k;

	j = 0;
	k = -1;
	len = ft_len(sh->var_env->name) + ft_len(sh->var_env->value);
	sh->tab_env[i] = (char *)malloc(sizeof(char) * (len + 2));
	if (!sh->tab_env[i])
		ft_error(sh, strerror(errno), NULL, NULL);
	while (sh->var_env->name[++k])
	{
		sh->tab_env[i][j] = sh->var_env->name[k];
		j++;
	}
	sh->tab_env[i][j] = '=';
	k = -1;
	j++;
	while (sh->var_env->value[++k])
	{
		sh->tab_env[i][j] = sh->var_env->value[k];
		j++;
	}
	sh->tab_env[i][len + 1] = '\0';
}

void	complete_tab(t_sh *sh)
{
	int	i;

	i = 0;
	while (sh->var_env->next != NULL)
	{
		fill_tab_value(sh, i);
		sh->var_env = sh->var_env->next;
		i++;
	}
	fill_tab_value(sh, i);
}

void	transform_env_tab(t_sh *sh)
{
	int			len;
	t_list_env	*temp;
	int			stop;

	stop = 0;
	len = 0;
	ft_free_tab(sh->tab_env);
	sh->alloue[7] = 0;
	temp = sh->var_env;
	while (sh->var_env->next != NULL)
	{
		sh->var_env = sh->var_env->next;
		len++;
	}
	len++;
	sh->var_env = temp;
	sh->tab_env = (char **)malloc(sizeof(char *) * (len + 1));
	if (!sh->tab_env)
		ft_error(sh, strerror(errno), NULL, NULL);
	sh->alloue[7] = 1;
	complete_tab(sh);
	sh->tab_env[len] = 0;
	sh->var_env = temp;
}

void	sort_tab_env(t_sh *sh, char **tableau)
{
	int	i;

	i = 0;
	while (tableau[i + 1])
	{
		if (ft_comp(tableau[i], tableau[i + 1]) > 0)
		{
			ft_swap(&tableau[i], &tableau[i + 1]);
			i = -1;
		}
		i++;
	}
}
