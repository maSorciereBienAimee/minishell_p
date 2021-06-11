/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_com.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 12:15:38 by ssar              #+#    #+#             */
/*   Updated: 2021/06/08 19:14:12 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

void	export_command(t_sh *sh, char *spl, char **lst, t_actual *actu)
{
	int			i;
	t_actual	*temp;

	sh->code = 0;
	if (actu->arg_command == 1)
	{
		sort_tab_env(sh, sh->tab_env);
		i = -1;
		while (sh->tab_env[++i])
		{
			write(1, sh->tab_env[i], ft_len(sh->tab_env[i]));
			write(1, "\n", 1);
		}
	}
	else
	{
		modify_env(sh, lst, 1);
		transform_env_tab(sh);
	}
}
