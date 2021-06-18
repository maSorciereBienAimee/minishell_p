/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 22:39:06 by ssar              #+#    #+#             */
/*   Updated: 2021/06/15 22:40:16 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

void	continue_boucle_cl(char *spl, int *dsb, int *i)
{
	if (spl[*i] == '"' && dsb[3] == 0 && dsb[1] % 2 == 0)
		dsb[4] += 0;
	else if (spl[*i] == '\'' && dsb[3] == 0 && dsb[0] % 2 == 0)
		dsb[4] += 0;
	else
		(dsb[4])++;
}

int	which_case_count(char *s, int *j, int *dsb)
{
	int	i;

	i = *j;
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

int	var_exit_status(t_sh *sh, int *i)
{
	int		count;
	char	*exit_str;

	count = 0;
	exit_str = ft_itoa(sh->last_exit);
	count = ft_len(exit_str);
	free(exit_str);
	(*i)++;
	return (count);
}
