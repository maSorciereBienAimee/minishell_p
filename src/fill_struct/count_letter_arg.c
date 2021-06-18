/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_letter_arg.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 12:51:18 by ssar              #+#    #+#             */
/*   Updated: 2021/06/15 22:41:58 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

char	*which_var_count(t_sh *sh, char *spl, int *i)
{
	int		count;
	int		j;
	char	*recup_var;
	int		k;
	char	*val;

	k = -1;
	j = 0;
	count = 0;
	while (is_al_num(spl[++(*i)]) == 1)
		j++;
	*i -= (j + 1);
	recup_var = (char *)malloc(sizeof(char) * (j + 1));
	if (!recup_var)
		ft_error(sh, strerror(errno), NULL, NULL);
	recup_var[j] = '\0';
	while (++k < j)
		recup_var[k] = spl[++(*i)];
	return (recup_var);
}

int	count_letter_no_qu(t_sh *sh, char *spl, int *i)
{
	int		count;
	char	*recup_var;
	int		k;
	char	*val;

	count = 0;
	recup_var = which_var_count(sh, spl, i);
	val = get_lst_value_of(sh, recup_var);
	free(recup_var);
	if (val != NULL)
	{
		k = 0;
		while (val[k])
		{
			while (val[k] && val[k] == ' ')
				k++;
			k--;
			while (val[++k] && val[k] != ' ')
				count++;
			if (val[k])
				count++;
		}
	}
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
	{
		if (spl[*i + 1] == '?')
			dsb[4] += var_exit_status(sh, i);
		else
		{
			if (which_case_count(spl, i, dsb) == 1)
				dsb[4] += count_letter_no_qu(sh, spl, i);
			if (which_case_count(spl, i, dsb) == 2)
				dsb[4] += count_letter_env(sh, spl, i);
			if (which_case_count(spl, i, dsb) == 3)
				(dsb[4])++;
		}
	}
	else
		continue_boucle_cl(spl, dsb, i);
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
