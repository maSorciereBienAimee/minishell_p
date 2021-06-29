/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 20:33:29 by ssar              #+#    #+#             */
/*   Updated: 2021/06/29 14:26:02 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

char	*stock_tab(t_sh *sh, char *my_tab, int i)
{
	char	*new_tab;
	int		j;

	j = 0;
	new_tab = (char *)malloc(sizeof(char) * i);
	if (!new_tab)
		ft_error(sh, strerror(errno), NULL, NULL);
	new_tab[i - 1] = '\0';
	while (my_tab[j])
	{
		new_tab[j] = my_tab[j];
		j++;
	}
	free(my_tab);
	return (new_tab);
}

char	*my_realloc(t_sh *sh, char *path, int i)
{
	char	*new_path;

	new_path = (char *)malloc(sizeof(char) * i);
	if (!new_path)
		ft_error(sh, strerror(errno), NULL, NULL);
	free(path);
	return (new_path);
}

char	*copy_end_char(t_sh *sh, char *spl, int count, int i)
{
	char	*ret;
	int		j;

	ret = (char *)malloc(sizeof(char) * (count + 1));
	if (!ret)
		ft_error(sh, strerror(errno), NULL, NULL);
	j = 0;
	while (j < count)
	{
		ret[j] = spl[i];
		j++;
		i++;
	}
	ret[j] = '\0';
	return (ret);
}
