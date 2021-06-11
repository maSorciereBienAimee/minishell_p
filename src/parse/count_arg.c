/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 12:48:58 by ssar              #+#    #+#             */
/*   Updated: 2021/06/09 14:44:06 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

void	count_arg(t_sh *sh, char *s, int *count, int i)
{
	int	q[4];
	int	j;

	j = -1;
	while (++j < 4)
		q[j] = 0;
	while (s[i] && ((i == 0 || s[i -1] != '\\') && ft_in(s[i], "<>|\n") != 1))
	{
		while ((s[i] == ' ' || s[i] == '\t') && s[i] != '\0')
			i++;
		check_if_in_quote(i, s, q);
		if (s[i] != ' ' && s[i] != '\t' && s[i] != '\0')
		{
			if ((ft_in(s[i], "<>|\n") == 1 && (i == 0 || s[i - 1] != '\\'))
				|| (ft_in(s[i], "<>|\n") == 1 && s[i - 1] == '\\' && q[3] == 0))
				break ;
			(*count)++;
		}
		while (s[i] && ((s[i] != ' ' && s[i] != '\t') || ((s[i] == ' '
						|| s[i] == '\t') && (q[0] % 2 != 0 || q[1] % 2 != 0))))
		{
			i++;
			check_if_in_quote(i, s, q);
		}
	}
}

void	recup_arg(t_sh *sh, char *spl, int *i, t_actual *ptr)
{
	int	j;
	int	k;
	int	letter;

	j = 0;
	while (spl[*i] && ((*i == 0 || spl[*i -1] != '\\')
			&& ft_in(spl[*i], "<>|\n") != 1) && j < ptr->arg_command)
	{
		skip_space(spl, i);
		k = *i;
		letter = count_letters(sh, spl, i);
		ptr->str_arg[j] = (char *)malloc(sizeof(char) * (letter + 1));
		if (!ptr->str_arg[j])
			ft_error(sh, strerror(errno), NULL, NULL);
		ptr->str_arg[j][letter] = '\0';
		fill_arg_cmd(sh, spl, k, &ptr->str_arg[j]);
		j++;
	}
}

void	there_is_suite(t_sh *sh, char *spl, int *i, t_actual *ptr)
{
	while (spl[*i] && (spl[*i] == ' ' || spl[*i] == '\t'))
		(*i)++;
	if (!spl[*i] || spl[*i] == '\n')
	{
		ptr->no_suite = 1;
		sh->end_cmd = 1;
	}
	else if (spl[*i] && spl[*i] == '>' && spl[*i + 1] != '>')
		ptr->redir_out = 1;
	else if (spl[*i] && spl[*i] == '>' && spl[*i + 1] == '>')
	{
		(*i)++;
		ptr->append = 1;
	}
	else if (spl[*i] && spl[*i] == '<' && spl[*i + 1] != '<')
		ptr->redir_in = 1;
	else if (spl[*i] && spl[*i] == '<' && spl[*i + 1] == '<')
	{
		(*i)++;
		ptr->redir_cur = 1;
	}
	else if (spl[*i] && spl[*i] == '|')
		ptr->pipe = 1;
	(*i)++;
}

t_actual	*get_arg_of_cmd(t_sh *sh, char *spl, int *i)
{
	int			j;
	int			count;
	t_actual	*ptr;

	j = 0;
	count = 0;
	ptr = (t_actual *)malloc(sizeof(t_actual));
	if (!ptr)
		ft_error(sh, strerror(errno), NULL, NULL);
	init_meta(ptr);
	while (spl[*i] && ft_in(spl[*i], " \t") == 1)
		(*i)++;
	count_arg(sh, spl, &count, *i);
	ptr->arg_command = count;
	ptr->str_arg = (char **)malloc(sizeof(char *) * (count + 1));
	if (!ptr->str_arg)
		ft_error(sh, strerror(errno), NULL, NULL);
	ptr->str_arg[count] = 0;
	recup_arg(sh, spl, i, ptr);
	there_is_suite(sh, spl, i, ptr);
	ptr->next = NULL;
	return (ptr);
}
