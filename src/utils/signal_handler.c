/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 20:09:19 by ssar              #+#    #+#             */
/*   Updated: 2021/06/08 16:42:16 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

t_gestion_sig	g_my_sig;

void	handler_sigint(int sig)
{
	int	i;

	i = -1;
	if (g_my_sig.exec_pid != -2 && g_my_sig.exec_pid != -3)
		kill(g_my_sig.exec_pid, SIGINT);
	if (g_my_sig.pid_suivant != -2)
		kill(g_my_sig.pid_suivant, SIGINT);
	else
	{
		close(g_my_sig.fd_out);
		g_my_sig.restart = 1;
	}
}

void	handler_sigquit(int sig)
{
	if (g_my_sig.exec_pid != -2)
		kill(g_my_sig.exec_pid, SIGQUIT);
	if (g_my_sig.pid_suivant != -2)
		kill(g_my_sig.pid_suivant, SIGQUIT);
	else
		write(2, "\b\b  \b\b", 6);
}
