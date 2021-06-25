/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redir_cur.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 14:52:20 by ssar              #+#    #+#             */
/*   Updated: 2021/06/25 09:31:54 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

t_gestion_sig	g_my_sig;

char	*get_next_word(t_sh *sh, char *spl, int i)
{
	int	count;
	int	dsb[4];

	count = -1;
	while (++count < 4)
		dsb[count] = 0;
	count = 0;
	while (spl[i] && (spl[i] == '<' || spl[i] == ' ' || spl[i] == '\t'))
		i++;
	check_if_in_quote(i, spl, dsb);
	while (end_arg(spl, i, dsb) == 0)
	{
		i++;
		count++;
		check_if_in_quote(i, spl, dsb);
	}
	i -= count;
	return (copy_end_char(sh, spl, count, i));
}

t_arg_redir	*create_arg_redir(t_sh *sh, char *spl, int *i, t_arg_redir *previus)
{
	char		*word;
	t_arg_redir	*ptr;
	int			stop;

	stop = 0;
	ptr = NULL;
	while (spl[*i] && stop == 0)
	{
		if (spl[*i] == '<' && spl[*i + 1] == '<')
			stop = 1;
		(*i)++;
	}
	if (spl[*i])
	{
		word = get_next_word(sh, spl, *i);
		ptr = (t_arg_redir *)malloc(sizeof(t_arg_redir));
		if (!ptr)
			ft_error(sh, strerror(errno), NULL, NULL);
		ptr->str = get_redir_arg(sh, word, 0);
		ptr->next = NULL;
		ptr->prev = previus;
		free(word);
		(*i)++;
	}
	return (ptr);
}

t_arg_redir	*get_all_redir_arg(t_sh *sh, char *spl)
{
	int			i;
	t_arg_redir	*temp;
	t_arg_redir	*ptr;
	t_arg_redir	*previous;

	i = 0;
	ptr = NULL;
	while (spl[i] && ptr == NULL)
		ptr = create_arg_redir(sh, spl, &i, NULL);
	while (spl[i])
	{
		previous = ft_lstlast_arg_redir(ptr);
		temp = create_arg_redir(sh, spl, &i, previous);
		if (temp != NULL)
			lst_add_back_arg_red(&ptr, temp);
		if (!spl[i])
			i--;
		i++;
	}
	return (ptr);
}

t_redir_cur	*new_cmd_arg(t_sh *sh, char *spl, int i)
{
	int			j;
	char		*word;
	t_redir_cur	*ptr;

	j = 0;
	ptr = (t_redir_cur *)malloc(sizeof(t_redir_cur));
	if (!ptr)
		ft_error(sh, strerror(errno), NULL, NULL);
	sh->alloue[12] = 1;
	ptr->j = i;
	ptr->next = NULL;
	ptr->arg = get_all_redir_arg(sh, spl);
	return (ptr);
}

void	get_redir_cur(t_sh *sh)
{
	int			i;
	t_redir_cur	*temp;

	i = 0;
	if (!sh->spl[i])
		return ;
	sh->redir = new_cmd_arg(sh, sh->spl[i], i);
	while (sh->spl[++i])
	{
		temp = new_cmd_arg(sh, sh->spl[i], i);
		lst_add_back_red(&sh->redir, temp);
	}
	sh->stock_redir = sh->redir;
	sh->stock_redir_arg = sh->redir->arg;
}
