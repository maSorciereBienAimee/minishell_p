/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nayache <nayache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 12:34:52 by nayache           #+#    #+#             */
/*   Updated: 2021/06/22 14:15:23 by nayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_H
# define HISTORY_H

# include "minishell.h"

typedef struct		s_hist
{
	int				nb;
	int				exist;
	char			*cmd;
	struct s_hist	*prev;
	struct s_hist	*next;
}					t_hist;

int			add_line_to_history(t_hist *history, char *line);
void		print_history(t_hist *history);
t_hist		*init_history(int exist);
t_hist		*build_history(int exist);
void		free_history(t_hist *history);
void		list_push_back(t_hist *head, t_hist *neew);
void		write_history(t_hist *history);
int			get_next_line(int fd, char **line);
#endif
