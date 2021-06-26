/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_readline_cur.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 14:55:16 by ssar              #+#    #+#             */
/*   Updated: 2021/06/26 09:33:56 by ssar             ###   ########.fr       */
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

void	init_readline(t_sh *sh, char **str, int *ij, char *buff)
{
	ij[0] = -1;
	ij[1] = 0;
	*str = (char *)malloc(sizeof(char) * 1);
	if (!(*str))
		ft_error(sh, strerror(errno), NULL, NULL);
	(*str)[0] = '\0';
	write(2, "> ", 2);
	while (++(ij[0]) < 4)
		buff[ij[0]] = 0;
	ij[0] = 2;
}

char	*my_readline(t_sh *sh)
{
	int		ij[2];
	char	*str;
	int		stop;
	int		a;
	char	buff[4];

	init_readline(sh, &str, ij, buff);
	stop = 0;
	while (stop != 1)
	{
		a = read(g_my_sig.fd_out, &buff, 4);
		if (a < 0 || (a == 0 && buff[0] == 0))
		{
			if (a == 0)
				write(2, "minishell : closed by EOF\n", 26);
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
