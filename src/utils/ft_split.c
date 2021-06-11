/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 12:04:25 by ssar              #+#    #+#             */
/*   Updated: 2021/06/02 17:08:42 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

static int	ft_count_letter(char const *s, char c, size_t u)
{
	int	count;

	count = 0;
	while (s[u] != c && s[u] != '\0')
	{
		count++;
		u++;
	}
	return (count);
}

static char	*ft_free(char **ptr, size_t i)
{
	while (i > 0)
	{
		i--;
		free((void *)ptr[i]);
	}
	free(ptr);
	return (NULL);
}

static char	**ft_fill(char **ptr, const char *s, char c, size_t nbr)
{
	int	i;
	int	u;
	int	j;
	int	letter;

	u = 0;
	i = 0;
	while (i < nbr)
	{
		while (s[u] == c)
			u++;
		letter = ft_count_letter(s, c, u);
		ptr[i] = (char *)malloc(sizeof(char) * (letter + 1));
		if (!ptr[i])
			return ((char **)ft_free(ptr, i));
		j = 0;
		while (j < letter)
			ptr[i][j++] = s[u++];
		ptr[i][j] = '\0';
		i++;
	}
	ptr[i] = 0;
	return (ptr);
}

static int	ft_count_w(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		if (s[i] != c && s[i] != '\0')
			count++;
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	int		nbr;
	char	**ptr;
	int		i;

	i = 0;
	if (!s)
		return (0);
	nbr = ft_count_w(s, c);
	ptr = (char **)malloc(sizeof(char *) * (nbr + 1));
	if (!ptr)
		return (NULL);
	ptr = ft_fill(ptr, s, c, nbr);
	return (ptr);
}
