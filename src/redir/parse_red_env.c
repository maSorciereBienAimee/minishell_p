/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_red_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 14:30:04 by ssar              #+#    #+#             */
/*   Updated: 2021/06/24 16:51:11 by ssar             ###   ########.fr       */
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

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			count += count_letter_env(sh, str, &i);
		else
			count++;
		i++;
	}
	return (count);
}

void	fill_red_env(t_sh *sh, char *old, char **new)
{
	int	ij[2];

	ij[0] = 0;
	ij[1] = -1;
	while (old[ij[0]])
	{
		if (old[ij[0]] == '$')
			case_env(sh, ij, old, new);
		else
		{
			(*new)[++(ij[1])] = old[ij[0]];
			(ij[0])++;
		}
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
