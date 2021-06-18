/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_arguments.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 18:54:55 by ssar              #+#    #+#             */
/*   Updated: 2021/06/15 22:50:24 by ssar             ###   ########.fr       */
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
	int		j;
	char	*recup_var;
	int		k;
	char	*val;

	k = -1;
	j = 0;
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

void	env_no_quote(t_sh *sh, char *s, int *ij, char **to_fill)
{
	char	*recup;
	char	*val;
	int		k;

	recup = which_var(sh, s, &(ij[0]));
	val = get_lst_value_of(sh, recup);
	free(recup);
	if (val != NULL)
	{
		k = 0;
		while (val[k])
		{
			while (val[k] && val[k] == ' ')
				k++;
			while (val[k] && val[k] != ' ')
			{
				(*to_fill)[++(ij[1])] = val[k];
				k++;
			}
			if (val[k])
				(*to_fill)[++(ij[1])] = ' ';
		}
	}
}

void	case_env(t_sh *sh, int *ij, char *s, char **to_fill)
{
	char	*recup;
	char	*val;
	int		k;

	recup = which_var(sh, s, &(ij[0]));
	val = get_lst_value_of(sh, recup);
	free(recup);
	if (val != NULL)
	{
		k = -1;
		while (val[++k])
			(*to_fill)[++(ij[1])] = val[k];
	}
}

void	fill_arg_cmd(t_sh *sh, char *s, int i, char **to_fill)
{
	int	ij[3];
	int	d[4];

	init_for_fill(s, d, ij, i);
	while (end_arg(s, ij[0], d) == 0)
	{
		if (debut_fill_arg(s, ij, d) == 1)
			ij[2] = 0;
		else if (s[ij[0]] == '$' && d[3] == 0)
		{
			if (s[ij[0] + 1] == '?')
				case_exit_status(sh, ij, to_fill);
			else if (which_case(s, ij, d) == 1)
				env_no_quote(sh, s, ij, to_fill);
			else if (which_case(s, ij, d) == 2)
				case_env(sh, ij, s, to_fill);
			else if (which_case(s, ij, d) == 3)
				(*to_fill)[++(ij[1])] = s[(ij[0])++];
		}
		else
			end_fill_arg(s, ij, d, to_fill);
		check_if_in_quote(ij[0], s, d);
	}
}
