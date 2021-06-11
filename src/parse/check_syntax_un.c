/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_un.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 19:25:55 by ssar              #+#    #+#             */
/*   Updated: 2021/06/08 16:17:43 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

int	error_quote( char c)
{
	write(2, "minishell: ", 11);
	write(2, "erreur de syntaxe pres du symbole inatendu \" ", 45);
	write(2, &c, 1);
	write(2, " \"\n", 3);
	return (-1);
}

int	check_form_redir_in(t_sh *sh, char *s, int *i, int *dsb)
{
	(*i)++;
	if (!s[*i] || s[*i] == ' ' || s[*i] == '\t')
	{
		if (is_error_syntax(sh, s, *i, "|;\n<>") == -1)
			return (-1);
	}
	if (s[*i] == '<')
	{
		if (is_error_syntax(sh, s, *i, "|;\n<>") == -1)
			return (-1);
	}
	return (1);
}

int	check_parenthese(char c, int *dsb)
{
	if (c == '(' && dsb[0] % 2 == 0 && dsb[1] % 2 == 0 && dsb[3] == 0)
		return (error_quote('('));
	if (c == ')' && dsb[0] % 2 == 0 && dsb[1] % 2 == 0 && dsb[3] == 0)
		return (error_quote(')'));
	if (c == '&' && dsb[0] % 2 == 0 && dsb[1] % 2 == 0 && dsb[3] == 0)
		return (error_quote('&'));
	if (c == '`' && dsb[0] % 2 == 0 && dsb[1] % 2 == 0 && dsb[3] == 0)
		return (error_quote('`'));
	return (1);
}

int	is_error_syntax(t_sh *sh, char *s, int i, char *err)
{
	int	k;

	k = i;
	if (s[i])
		i++;
	while ((s[i] == ' ' || s[i] == '\t') && s[i])
		i++;
	if (!s[i] || ft_in(s[i], err) == 1)
	{
		write(2, "minishell: ", 11);
		write(2, "erreur de syntaxe pres du symbole inatendu \" ", 45);
		if (!s[i] || s[i] == '\n')
			write(2, "newline", 7);
		else
			write(2, &s[i], 1);
		write(2, " \"\n", 3);
		return (-1);
	}
	return (1);
}

int	check_format_pipe(t_sh *sh, char **ptr)
{
	int	i;
	int	j;
	int	k;
	int	dsb[4];

	i = -1;
	while (++i < 4)
		dsb[i] = 0;
	i = -1;
	while (ptr[++i])
	{
		j = 0;
		while (ptr[i][j] && (ptr[i][j] == ' ' || ptr[i][j] == '\t'))
			j++;
		if (ptr[i][j] == '|')
		{
			write(2, "minishell: ", 11);
			write(2, "erreur de syntaxe pres du symbole inatendu \" ", 45);
			write(2, &ptr[i][j], 1);
			write(2, " \"\n", 3);
			return (-1);
		}
	}
	return (1);
}
