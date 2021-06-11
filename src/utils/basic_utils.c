/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 17:10:06 by ssar              #+#    #+#             */
/*   Updated: 2021/06/09 15:10:13 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

int	ft_len(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*copy_char(t_sh *sh, char *dest, char *source)
{
	int	i;
	int	len;

	if (dest != NULL)
		free(dest);
	len = ft_len(source);
	dest = (char *)malloc(sizeof(char) * (len + 1));
	if (!dest)
		ft_error(sh, strerror(errno), NULL, NULL);
	i = -1;
	while (++i < len)
		dest[i] = source[i];
	dest[i] = '\0';
	return (dest);
}

int	ft_comp(char *str, char *str2)
{
	int	i;

	i = 0;
	if (str == NULL && str2 == NULL)
		return (0);
	if (str == NULL && str2 != NULL)
		return (-1);
	if (str != NULL && str2 == NULL)
		return (-1);
	while (str[i] && str2[i] && str[i] == str2[i])
		i++;
	return ((unsigned char)str[i] - (unsigned char)str2[i]);
}

int	ft_in(char c, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_free_tab(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i] != 0)
	{
		free((void *)ptr[i]);
		i++;
	}
	free(ptr);
	return (NULL);
}
