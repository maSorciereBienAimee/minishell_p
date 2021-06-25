/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_red_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 14:30:04 by ssar              #+#    #+#             */
/*   Updated: 2021/06/25 22:07:47 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

int	is_env_apply(char *word, char *str)
{
	int	i;

	i = 0;
	while (word[i])
	{
		if (word[i] == '\\' || word[i] == '\'' || word[i] == '"')
			return (0);
		i++;
	}
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

int	count_red_env(t_sh *sh, char *str)
{
	int	i;
	int	count;
	int	dsb[4];

	count = 0;
	i = -1;
	while (++i < 4)
		dsb[i] = 0;
	i = 0;
	check_if_in_quote(i, str, dsb);
	while (str[i])
	{
		if (str[i] == '\\' && dsb[3] == 0)
			count += 0;
		else if (str[i] == '\\' && dsb[3] == 0 && (str[i + 1] == '$'))
			count += 0;
		else if (str[i] == '$' && dsb[3] == 0)
			count += count_letter_env(sh, str, &i);
		else
			count++;
		i++;
		if (str[i])
			check_if_in_quote(i, str, dsb);
	}
	return (count);
}

void	fill_red_env(t_sh *sh, char *old, char **new)
{
	int	ij[2];
	int	dsb[4];
	int	i;

	i = -1;
	while (++i < 4)
		dsb[i] = 0;
	ij[0] = 0;
	ij[1] = -1;
	check_if_in_quote(ij[0], old, dsb);
	while (old[ij[0]])
	{
		if (old[ij[0]] == '\\' && dsb[3] == 0)
			(ij[0])++;
		else if (old[ij[0]] == '\\' && dsb[3] == 0 && (old[ij[0] + 1] == '$'))
			(ij[0])++;
		else if (old[ij[0]] == '$' && dsb[3] == 0)
			case_env(sh, ij, old, new);
		else
		{
			(*new)[++(ij[1])] = old[ij[0]];
			(ij[0])++;
		}
		check_if_in_quote(ij[0], old, dsb);
	}
}

char	*get_new_red(t_sh *sh, char *stock)
{
	int		i;
	char	*new;
	int		count;

	i = 0;
	count = count_red_env(sh, stock);
	new = (char *)malloc(sizeof(char) * (count + 1));
	if (!new)
		return (NULL);
	fill_red_env(sh, stock, &new);
	new[count] = '\0';
	free(stock);
	return (new);
}

void	parse_redir(t_sh *sh, char *word, char **stock)
{
	int	i;

	i = 0;
	if (stock == NULL)
		return ;
	while (stock[i])
	{
		if (is_env_apply(word, stock[i]) == 1)
		{
			stock[i] = get_new_red(sh, stock[i]);
			if (!stock[i])
			{
				ft_error(sh, strerror(errno), NULL, NULL);
				return ;
			}
		}
		i++;
	}
}
