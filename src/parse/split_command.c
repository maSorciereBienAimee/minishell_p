/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 12:04:25 by ssar              #+#    #+#             */
/*   Updated: 2021/06/07 10:20:26 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

static size_t	ft_count_letter(char *s, char c, size_t u)
{
	size_t	count;
	int		dsb[4];
	int		stop;

	count = 0;
	stop = 0;
	dsb[0] = 0;
	dsb[1] = 0;
	dsb[2] = 0;
	dsb[3] = 0;
	while (s[u] != '\0')
	{
		check_if_in_quote(u, s, dsb);
		if ((s[u] == c && dsb[0] % 2 == 0 && dsb[1] % 2 == 0) || s[u] == '\n')
			break ;
		count++;
		u++;
	}
	return (count);
}

static char	*ft_free_t(char **ptr, size_t i)
{
	while (i > 0)
	{
		i--;
		free((void *)ptr[i]);
	}
	free(ptr);
	return (NULL);
}

static char	**ft_fill(char **ptr, char *s, char c, size_t nbr)
{
	size_t	i;
	size_t	u;
	size_t	j;
	size_t	letter;

	u = 0;
	i = 0;
	while (i < nbr)
	{
		while (s[u] == c)
			u++;
		letter = ft_count_letter(s, c, u);
		ptr[i] = (char *)malloc(sizeof(char) * (letter + 1));
		if (!ptr[i])
			return ((char **)ft_free_t(ptr, i));
		j = 0;
		while (j < letter)
			ptr[i][j++] = s[u++];
		ptr[i][j] = '\0';
		i++;
	}
	ptr[i] = 0;
	return (ptr);
}

int	ft_count_w(char *s, char c)
{
	int	i;
	int	count;
	int	dsb[4];

	i = -1;
	count = 0;
	while (++i < 4)
		dsb[i] = 0;
	i = 0;
	while (s[i])
	{
		i--;
		while (s[++i] == c && s[i] != '\0')
			check_if_in_quote(i, s, dsb);
		if (s[i] != c && dsb[0] % 2 == 0 && dsb[0] % 2 == 0 && s[i] != '\0')
			count++;
		i--;
		while (s[++i] != c && s[i] != '\0')
			check_if_in_quote(i, s, dsb);
	}
	if (dsb[0] % 2 != 0)
		return (error_quote('"'));
	if (dsb[1] % 2 != 0)
		return (error_quote('\''));
	return (count);
}

char	**ft_split_commande(t_sh *sh, char *s, char c)
{
	size_t	nbr;
	char	**ptr;
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	if (sh->alloue[2] == 1)
		ft_free_tab(sh->spl);
	sh->alloue[2] = 0;
	if (check_format_virgule(sh, s) == -1)
		return (NULL);
	if (check_format_global(sh, s) == -1)
		return (NULL);
	nbr = ft_count_w(s, c);
	if (nbr == -1)
		return (NULL);
	ptr = (char **)malloc(sizeof(char *) * (nbr + 1));
	if (!ptr)
		ft_error(sh, strerror(errno), NULL, NULL);
	ptr = ft_fill(ptr, s, c, nbr);
	if (check_format_pipe(sh, ptr) == -1)
		return ((char **)ft_free_t(ptr, nbr));
	sh->alloue[2] = 1;
	return (ptr);
}
