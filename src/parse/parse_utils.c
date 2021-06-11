/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 16:28:15 by ssar              #+#    #+#             */
/*   Updated: 2021/06/02 10:16:31 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

void	skip_space(char *spl, int *i)
{
	while (spl[*i] && ft_in(spl[*i], " \t") == 1)
		(*i)++;
}

void	skip(char *spl, int *i)
{
	while (spl[*i] && ft_in(spl[*i], " \t") != 1)
		(*i)++;
	while (spl[*i] && ft_in(spl[*i], " \t") == 1)
		(*i)++;
}

int	end_arg(char *spl, int i, int *q)
{
	if (!spl[i]
		|| (ft_in(spl[i], "<>|\n") == 1 && q[3] == 0
			&& q[0] % 2 == 0 && q[1] % 2 == 0)
		|| ((spl[i] == ' ' || spl[i] == '\t')
			&& (q[0] % 2 == 0 && q[1] % 2 == 0)))
		return (1);
	return (0);
}

void	check_back_slash(int *i, char *spl, int j, int *dsb)
{
	if (*i == 0 && spl[j] == '\\' && (dsb[1] % 2 == 0
			|| (dsb[1] % 2 != 0 && (!spl[j + 1] || spl[j + 1] != '\''))))
		*i = 1;
	else
		*i = 0;
}

void	check_if_in_quote(int i, char *s, int *dsb)
{
	dsb[3] = dsb[2];
	check_back_slash(&dsb[2], s, i, dsb);
	if ((s[i] == '\'' && dsb[0] % 2 == 0
			&& (!s[i - 1] || s[i - 1] != '\\'))
		|| (s[i] == '\'' && dsb[0] % 2 == 0
			&& dsb[1] % 2 == 0 && s[i - 1] == '\\' && dsb[3] == 0)
		|| (s[i] == '\'' && dsb[1] % 2 == 1))
		dsb[1]++;
	if ((s[i] == '"' && dsb[1] % 2 == 0
			&& (!s[i - 1] || s[i - 1] != '\\'))
		|| (s[i] == '"' && dsb[1] % 2 == 0
			&& s[i - 1] == '\\' && dsb[3] == 0))
		dsb[0]++;
}
