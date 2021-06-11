/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_letter_arg.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 12:51:18 by ssar              #+#    #+#             */
/*   Updated: 2021/06/07 10:21:40 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

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

int	count_letter_env(t_sh *sh, char *spl, int *i)
{
	int		count;
	int		j;
	char	*recup_var;
	int		k;

	k = -1;
	j = 0;
	count = 0;
	if (spl[*i + 1] == '?')
		return (var_exit_status(sh, i));
	while (is_al_num(spl[++(*i)]) == 1)
		j++;
	*i -= (j + 1);
	recup_var = (char *)malloc(sizeof(char) * (j + 1));
	if (!recup_var)
		ft_error(sh, strerror(errno), NULL, NULL);
	recup_var[j] = '\0';
	while (++k < j)
		recup_var[k] = spl[++(*i)];
	count = ft_len(get_lst_value_of(sh, recup_var));
	free(recup_var);
	return (count);
}

void	boucle_count_letters(t_sh *sh, char *spl, int *i, int *dsb)
{
	if (spl[*i] == '\\' && dsb[3] == 0
		&& dsb[0] % 2 == 0 && dsb[1] % 2 == 0)
		dsb[4] += 0;
	else if (spl[*i] == '\\' && dsb[3] == 0
		&& dsb[0] % 2 == 1 && (spl[*i + 1] == '$' || spl[*i + 1] == '`'
			|| spl[*i + 1] == '"' || spl[*i + 1] == '\\'))
		dsb[4] += 0;
	else if (spl[*i] == '$' && dsb[3] == 0)
		dsb[4] += count_letter_env(sh, spl, i);
	else if (spl[*i] == '"' && dsb[3] == 0 && dsb[1] % 2 == 0)
		dsb[4] += 0;
	else if (spl[*i] == '\'' && dsb[3] == 0 && dsb[0] % 2 == 0)
		dsb[4] += 0;
	else
		(dsb[4])++;
	(*i)++;
	check_if_in_quote(*i, spl, dsb);
}

int	count_letters(t_sh *sh, char *spl, int *i)
{
	int	j;
	int	dsb[5];

	j = -1;
	while (++j < 5)
		dsb[j] = 0;
	check_if_in_quote(*i, spl, dsb);
	while (end_arg(spl, *i, dsb) == 0)
		boucle_count_letters(sh, spl, i, dsb);
	return (dsb[4]);
}
