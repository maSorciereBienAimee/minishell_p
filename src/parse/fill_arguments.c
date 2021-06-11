/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_arguments.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 18:54:55 by ssar              #+#    #+#             */
/*   Updated: 2021/06/07 10:20:45 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

char	*fill_var_exit_status(t_sh *sh, int *i)
{
	int		count;
	char	*exit_str;

	count = 0;
	exit_str = ft_itoa(sh->last_exit);
	(*i)++;
	return (exit_str);
}

char	*which_var(t_sh *sh, char *spl, int *i)
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
	(*i)++;
	return (recup_var);
}

void	case_env(t_sh *sh, int *ij, char *spl, char **to_fill)
{
	char	*recup;
	char	*val;
	int		k;

	if (spl[ij[0] + 1] == '?')
	{
		val = ft_itoa(sh->last_exit);
		ij[0] +=2;
		k = -1;
		while (val[++k])
			(*to_fill)[++(ij[1])] = val[k];
		free(val);
	}
	else
	{
		recup = which_var(sh, spl, &(ij[0]));
		val = get_lst_value_of(sh, recup);
		free(recup);
		if (val != NULL)
		{
			k = -1;
			while (val[++k])
				(*to_fill)[++(ij[1])] = val[k];
		}
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

void	fill_arg_cmd(t_sh *sh, char *s, int i, char **to_fill)
{
	int	ij[2];
	int	d[4];

	init_for_fill(s, d, ij, i);
	while (end_arg(s, ij[0], d) == 0)
	{
		if (s[ij[0]] == '\\' && d[3] == 0 && d[0] % 2 == 0 && d[1] % 2 == 0)
			(ij[0])++;
		else if (s[ij[0]] == '\\' && d[3] == 0
			&& d[0] % 2 == 1 && (s[ij[0] + 1] == '$' || s[ij[0] + 1] == '`'
				|| s[ij[0] + 1] == '"' || s[ij[0] + 1] == '\\'))
			(ij[0])++;
		else if (s[ij[0]] == '$' && d[3] == 0)
			case_env(sh, ij, s, to_fill);
		else if (s[ij[0]] == '"' && d[3] == 0 && d[1] % 2 == 0)
			(ij[0])++;
		else if (s[ij[0]] == '\'' && d[3] == 0 && d[0] % 2 == 0)
			(ij[0])++;
		else
		{
			(*to_fill)[++(ij[1])] = s[ij[0]];
			(ij[0])++;
		}
		check_if_in_quote(ij[0], s, d);
	}
}
