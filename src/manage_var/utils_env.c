/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 16:48:52 by ssar              #+#    #+#             */
/*   Updated: 2021/06/08 17:13:37 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

void	print_env(t_sh *sh)
{
	while (sh->var_env)
	{
		write(1, sh->var_env->name, ft_len(sh->var_env->name));
		write(1, "=", 1);
		write(1, sh->var_env->value, ft_len(sh->var_env->value));
		write(1, "\n", 1);
		sh->var_env = sh->var_env->next;
	}
}

char	*get_name(t_sh *sh, char *str)
{
	int		i;
	int		j;
	char	*ret;

	i = 0;
	j = -1;
	while (str[i] != '=')
		i++;
	ret = (char *)malloc(sizeof(char) * (i + 1));
	if (!ret)
		ft_error(sh, strerror(errno), NULL, NULL);
	while (++j < i)
		ret[j] = str[j];
	ret[i] = '\0';
	return (ret);
}

char	*get_value(t_sh *sh, char *str)
{
	int		i;
	int		j;
	int		k;
	char	*ret;
	int		stock;

	i = 0;
	j = 0;
	k = -1;
	while (str[i] != '=')
		i++;
	stock = i;
	while (str[++i] != '\0')
		j++;
	i = stock;
	ret = (char *)malloc(sizeof(char) * (j + 1));
	if (!ret)
		ft_error(sh, strerror(errno), NULL, NULL);
	while (++k < j)
		ret[k] = str[++i];
	ret[j] = '\0';
	return (ret);
}

int	is_name_eq_value(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}
