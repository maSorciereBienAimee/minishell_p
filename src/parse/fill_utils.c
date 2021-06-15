/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 22:46:31 by ssar              #+#    #+#             */
/*   Updated: 2021/06/15 22:47:46 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

int	debut_fill_arg(char *s, int *ij, int *d)
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

void	case_exit_status(t_sh *sh, int *ij, char **to_fill)
{
	char	*val;
	int		k;

	val = ft_itoa(sh->last_exit);
	ij[0] +=2;
	k = -1;
	while (val[++k])
		(*to_fill)[++(ij[1])] = val[k];
	free(val);
}

void	end_fill_arg(char *s, int *ij, int *d, char **to_fill)
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

void	init_for_fill(char *spl, int *dsb, int *ij, int i)
{
	int	k;

	k = -1;
	while (++k < 4)
		dsb[k] = 0;
	ij[0] = i;
	ij[1] = -1;
	check_if_in_quote(ij[0], spl, dsb);
}

int	which_case(char *s, int *ij, int *dsb)
{
	int	i;

	i = ij[0];
	if (dsb[0] % 2 == 0 && dsb[1] % 2 == 0)
		return (1);
	if (dsb[0] % 2 != 0 && dsb[1] % 2 == 0)
		return (2);
	if (dsb[0] % 2 == 0 && dsb[1] % 2 != 0)
		return (3);
	if (dsb[0] % 2 != 0 && dsb[1] % 2 != 0)
	{
		while (s[i] && s[i] != '\'' && s[i] != '"')
		{
			if (s[i] == '\'')
				return (2);
			if (s[i] == '"')
				return (3);
			i++;
		}
	}
	return (-1);
}
