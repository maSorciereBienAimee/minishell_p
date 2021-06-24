/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_delimit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 14:30:19 by ssar              #+#    #+#             */
/*   Updated: 2021/06/24 14:30:22 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

int	debut_fill_red(char *s, int *ij, int *d)
{
	if (s[ij[0]] == '\\' && d[3] == 0 && d[0] % 2 == 0 && d[1] % 2 == 0)
	{
		(ij[0])++;
		return (1);
	}
	else if (s[ij[0]] == '\\' && d[3] == 0
		&& d[0] % 2 == 1 && (s[ij[0] + 1] == '$' || s[ij[0] + 1] == '`'
			|| s[ij[0] + 1] == '"' || s[ij[0] + 1] == '\\'))
	{
		(ij[0])++;
		return (1);
	}
	return (0);
}

void	end_fill_red(char *s, int *ij, int *d, char **to_fill)
{
	if (s[ij[0]] == '"' && d[3] == 0 && d[1] % 2 == 0)
		(ij[0])++;
	else if (s[ij[0]] == '\'' && d[3] == 0 && d[0] % 2 == 0)
		(ij[0])++;
	else
	{
		(*to_fill)[++(ij[1])] = s[ij[0]];
		(ij[0])++;
	}
}

void	fill_arg_red(t_sh *sh, char *s, int i, char **to_fill)
{
	int	ij[3];
	int	d[4];

	init_for_fill(s, d, ij, i);
	while (s[ij[0]])
	{
		if (debut_fill_red(s, ij, d) == 1)
			ij[2] = 0;
		else
			end_fill_red(s, ij, d, to_fill);
		check_if_in_quote(ij[0], s, d);
	}
}

void	continue_boucle_cl_red(char *spl, int *dsb, int *i)
{
	if (spl[*i] == '"' && dsb[3] == 0 && dsb[1] % 2 == 0)
		dsb[4] += 0;
	else if (spl[*i] == '\'' && dsb[3] == 0 && dsb[0] % 2 == 0)
		dsb[4] += 0;
	else
		(dsb[4])++;
}

void	boucle_count_letter_red(t_sh *sh, char *spl, int *i, int *dsb)
{
	if (spl[*i] == '\\' && dsb[3] == 0
		&& dsb[0] % 2 == 0 && dsb[1] % 2 == 0)
		dsb[4] += 0;
	else if (spl[*i] == '\\' && dsb[3] == 0
		&& dsb[0] % 2 == 1 && (spl[*i + 1] == '$' || spl[*i + 1] == '`'
			|| spl[*i + 1] == '"' || spl[*i + 1] == '\\'))
		dsb[4] += 0;
	else if (spl[*i] == '"' && dsb[3] == 0 && dsb[1] % 2 == 0)
		dsb[4] += 0;
	else if (spl[*i] == '\'' && dsb[3] == 0 && dsb[0] % 2 == 0)
		dsb[4] += 0;
	else
		(dsb[4])++;
	//	continue_boucle_cl_red(spl, dsb, i);
	(*i)++;
	check_if_in_quote(*i, spl, dsb);
}

int	count_l_red(t_sh *sh, char *spl, int *i)
{
	int	j;
	int	dsb[5];

	j = -1;
	while (++j < 5)
		dsb[j] = 0;
	check_if_in_quote(*i, spl, dsb);
	while (spl[*i])
		boucle_count_letter_red(sh, spl, i, dsb);
	return (dsb[4]);
}

char *parse_delimiteur(t_sh *sh, char *str)
{
	char *new;
	int letters;
	int i;
	int j;

	j = 0;
	i = 0;
	letters = count_l_red(sh, str, &i);
	new = (char *)malloc(sizeof(char) * (letters + 1));
	if (!new)
	{
		ft_error(sh, strerror(errno), NULL, NULL);
		return (NULL);
	}
	new[letters] = '\0';
	fill_arg_red(sh, str, 0, &new);
	return (new);
}
