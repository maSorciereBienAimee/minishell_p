/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 11:33:36 by ssar              #+#    #+#             */
/*   Updated: 2021/06/11 12:43:13 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

t_gestion_sig	g_my_sig;

int	check_touche_b(t_sh*sh, char *b, int *ij, char **str)
{
	int	k;

	k = 0;
	while (k < 4)
	{
		if (b[k] == EOF || b[k] == '\0')
			return (0);
		if (b[k] == '\n')
			return (1);
		if (b[k] != 127 && b[k] >= 32)
		{
			*str = stock_tab(sh, *str, ij[0]);
			(*str)[ij[1]] = b[k];
			(*str)[ij[0] - 1] = '\0';
			ij[0]++;
			ij[1]++;
		}
		k++;
	}
	return (0);
}

int	check_touche(t_sh*sh, char *b, int *j, int *i)
{
	int	k;

	k = 0;
	while (k < 4)
	{
		if (b[k] == EOF || b[k] == '\0')
			return (0);
		if (b[k] == '\n')
			return (1);
		if (b[k] != 127 && b[k] >= 32)
		{
			sh->command = stock_tab(sh, sh->command, *i);
			sh->command[*j] = b[k];
			sh->command[*i - 1] = '\0';
			(*i)++;
			(*j)++;
		}
		else
			printf("fleche\n");
		k++;
	}
	return (0);
}

int	read_quit(t_sh *sh, int a, char *buff)
{
	if (a < 0)
	{
		sh->alloue[11] = 0;
		sh->last_exit = 130;
		g_my_sig.restart = 1;
		return (-1);
	}
	if (a == 0)
	{
		if (buff[0] == 0)
		{
			my_free(sh);
			if (sh->alloue[7] == 1)
				ft_free_tab(sh->tab_env);
			sh->alloue[7] = 0;
			close(sh->save_stdout);
			exit(sh->last_exit);
		}
	}
	return (1);
}

char	*my_readline(t_sh *sh)
{
	int		ij[2];
	char	*str;
	int		stop;
	int		a;
	char	buff[4];

	ij[0] = -1;
	ij[1] = 0;
	stop = 0;
	str = (char *)malloc(sizeof(char) * 1);
	if (!str)
		ft_error(sh, strerror(errno), NULL,NULL);
	str[0] = '\0';
	write(1, "> ", 2);
	while (++(ij[0]) < 4)
		buff[ij[0]] = 0;
	ij[0] = 2;
	while (stop != 1)
	{
		a = read(g_my_sig.fd_out, &buff, 4);
		if (a == 0 && buff[0] == 0)
		{
			free(str);
			return (NULL);
		}
		stop = check_touche_b(sh, buff, ij, &str);
		a = -1;
		while (++a < 4)
			buff[a] = 0;
	}
	return (str);
}

char *get_next_word(t_sh *sh, char *spl, int i)
{
	char *ret;
	int count;
	int j;

	count = 0;
	while (spl[i] && (spl[i] == '<' || spl[i] == ' ' || spl[i] == '\t'))
		i++;
	while (spl[i] && ft_in(spl[i], " \t<>|;\n") == 0)
	{
		i++;
		count++;
	}
	i -= count;
	ret = (char *)malloc(sizeof(char) * (count + 1));
	if (!ret)
		ft_error(sh, strerror(errno), NULL, NULL);
	j = 0;
	while (j < count)
	{
		ret[j] = spl[i];
		j++;
		i++;
	}
	ret[j] = '\0';
	return (ret);
}

int	fill_redir_cur(char **new, char **stock, char *c)
{
	int i;
	int j;

	i = 0;
	if (stock != NULL)
	{
		i = -1;
		while(stock[++i])
		{
			new[i] = (char *)malloc(sizeof(char) * (ft_len(stock[i]) + 2));
			if (!new[i])
				return (-1);
			j = -1;
			while (stock[i][++j])
				new[i][j] = stock[i][j];
			new[i][j] = '\0';
		}
	}
	new[i] = (char *)malloc(sizeof(char) * (ft_len(c) + 1));
	if (!new[i])
		return (-1);
	j = -1;
	while (c[++j])
		new[i][j] = c[j];
	new[i][j] = '\0';
	return (1);
}

char	**stock_redir_cur(char **stock, char *c)
{
	int i;
	char **new;

	i = 0;
	if (stock == NULL)
		i = 0;
	else
	{
		while(stock[i] != 0)
			i++;
	}
	new = (char **)malloc(sizeof(char *) * (i + 2));
	if(!new)
		return (NULL);
	if (fill_redir_cur(new, stock, c) == -1)
	{
		if (stock != NULL)
			ft_free_tab(stock);
		ft_free_tab(new);
		return (NULL);
	}
	new[i + 1] = 0;
	if (stock != NULL)
		ft_free_tab(stock);
	return (new);
}

char	**get_redir_arg(t_sh *sh, char *word)
{
	char	*str;
	t_actual *temp;
	char **stock;
	int stop;

	stop = 0;
	str = NULL;
	stock = NULL;
	while (stop == 0)
	{
		str = my_readline(sh);
		//str = readline("> ");
		if (str == NULL || (ft_comp(str, word) == 0))
		{	
			if (str == NULL)
				write(2, "Closed by EOF\n",14);
			stop = 1;
			break ;
		}
		stock = stock_redir_cur(stock, str);
		if (stock == NULL)
			ft_error(sh, strerror(errno), NULL, NULL);
		free(str);
	}
	if (str != NULL)
		free(str);
	return (stock);
}

t_arg_redir	*create_arg_redir(t_sh *sh, char *spl, int *i)
{
	char *word;
	t_arg_redir *ptr;
	int stop;

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
		ptr->str = get_redir_arg(sh, word);
		ptr->next = NULL;
		free(word);
		(*i)++;
	}
	return (ptr);
}

t_arg_redir	*get_all_redir_arg(t_sh *sh, char *spl)
{
	int i;
	t_arg_redir	*temp;
	t_arg_redir	*ptr;

	i = 0;
	ptr = NULL;
	while (spl[i] && ptr == NULL)
		ptr = create_arg_redir(sh, spl, &i);
	while (spl[i])
	{
		temp = create_arg_redir(sh, spl, &i);
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
	int j;
	char *word;
	t_redir_cur *ptr;

	j = 0;
	ptr = (t_redir_cur *)malloc(sizeof(t_redir_cur));
	if(!ptr)
		ft_error(sh, strerror(errno), NULL, NULL);
	sh->alloue[12] = 1;
	ptr->j = i;
	ptr->next = NULL;
	ptr->arg = get_all_redir_arg(sh, spl);
	return (ptr);
}
//	ptr->arg = NULL;
//	while (spl[j])
//	{
//		if (spl[j] == '<' && spl[j + 1] == '<')
//		{
		//	if (ptr->arg != NULL)
		//	{
		//		ft_free_tab(ptr->arg);
		//		ptr->arg = NULL;
		//	}
//			word = get_next_word(sh, spl, j);
			//			free(word);
//		}
//		j++;
//	}

void	get_redir_cur(t_sh *sh)
{
	int i;
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

void	get_command(t_sh *sh)
{
	int		i;
	int		j;
	int		stop;
	int		a;
	char	buff[4];

	i = -1;
	j = 0;
	stop = 0;
	write(1, "minishell $> ", 13);
	while (++i < 4)
		buff[i] = 0;
	i = 2;
	while (stop != 1)
	{
		a = read(g_my_sig.fd_out, &buff, 4);
		if (read_quit(sh, a, buff) == -1)
			return ;
		stop = check_touche(sh, buff, &j, &i);
		a = -1;
		while (++a < 4)
			buff[a] = 0;
	}
	sh->spl = ft_split_commande(sh, sh->command, ';');
	get_redir_cur(sh);



//	t_redir_cur *temp;
//	temp = sh->redir;
//	t_arg_redir *redir;
//	while (sh->redir)
//	{
//		printf("\ncommande :\n");
//		redir = sh->redir->arg;
//		while (sh->redir->arg)
//		{
//			printf("\nmeta :\n");
//			int o = 0;
//			while (sh->redir->arg->str[o])
//			{
//				printf("%s\n", sh->redir->arg->str[o]);
//				o++;
//			}
//			sh->redir->arg = sh->redir->arg->next;
//		}
//		sh->redir->arg = redir;
//		sh->redir = sh->redir->next;
//	}
//	sh->redir = temp;
}
