/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_deux.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 19:31:25 by ssar              #+#    #+#             */
/*   Updated: 2021/06/08 16:34:51 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

int	check_form_redir(t_sh *sh, char *s, int *i, int *dsb)
{
	(*i)++;
	if (!s[*i] || s[*i] == ' ' || s[*i] == '\t')
	{
		if (is_error_syntax(sh, s, *i, "|;\n<>") == -1)
			return (-1);
	}
	if (s[*i] == '>')
	{
		if (is_error_syntax(sh, s, *i, "|;\n<>") == -1)
			return (-1);
	}
	return (1);
}

int	check_form_global_bis(t_sh *sh, char *s, int *i, int *dsb)
{
	if (s[*i] == '|' && dsb[0] % 2 == 0 && dsb[1] % 2 == 0 && dsb[3] == 0)
	{
		if (is_error_syntax(sh, s, *i, "|;\n<>") == -1)
			return (-1);
	}
	if (s[*i] == '<' && dsb[0] % 2 == 0 && dsb[1] % 2 == 0 && dsb[3] == 0)
	{
		if (check_form_redir_in(sh, s, i, dsb) == -1)
			return (-1);
	}
	if (s[*i] == '>' && dsb[0] % 2 == 0 && dsb[1] % 2 == 0 && dsb[3] == 0)
	{
		if (check_form_redir(sh, s, i, dsb) == -1)
			return (-1);
	}
	return (1);
}

int	check_format_global(t_sh *sh, char *s)
{
	int	i;
	int	dsb[4];
	int	j;

	i = -1;
	j = -1;
	while (++j < 4)
		dsb[j] = 0;
	while (s[++i])
	{
		while (s[i] && ft_in(s[i], "|><") == 0)
		{
			check_if_in_quote(i, s, dsb);
			if (check_parenthese(s[i], dsb) == -1)
				return (-1);
			i++;
		}
		check_if_in_quote(i, s, dsb);
		if (check_form_global_bis(sh, s, &i, dsb) == -1)
			return (-1);
		if (!s[i])
			i--;
	}
	return (1);
}

int	check_form_virgule_bis(t_sh *sh, char *s, int i)
{
	write(2, "minishell: ", 11);
	write(2, "erreur de syntaxe pres du symbole inatendu \" ", 45);
	write(2, &s[i], 1);
	write(2, " \"\n", 3);
	sh->last_exit = 1;
	return (-1);
}

int	check_format_virgule(t_sh *sh, char *s)
{
	int	i;
	int	dsb[4];

	i = -1;
	while (++i < 4)
		dsb[i] = 0;
	i = -1;
	while (s[++i])
	{
		i--;
		while (s[++i] && s[i] != ';')
			check_if_in_quote(i, s, dsb);
		if (s[i] == ';' && dsb[0] % 2 == 0 && dsb[1] % 2 == 0)
		{
			i++;
			while (s[i] && (s[i] == ' ' || s[i] == '\t'))
				i++;
			if (s[i] == ';')
				return (check_form_virgule_bis(sh, s, i));
		}
		if (!s[i])
			i--;
	}
	return (1);
}
