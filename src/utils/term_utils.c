/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 18:00:16 by ssar              #+#    #+#             */
/*   Updated: 2021/06/21 18:00:37 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

void	pass_non_canonique(t_sh *sh)
{
	tcgetattr(0, &sh->old_tty);
	ft_bzero(&sh->new_tty, sizeof(sh->new_tty));
	sh->new_tty.c_cflag = CREAD;
	sh->new_tty.c_iflag = IGNPAR | ICRNL;
	sh->new_tty.c_oflag = 0;
	sh->new_tty.c_lflag = 0;
	sh->new_tty.c_cc[VMIN] = 1;
	sh->new_tty.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &sh->new_tty);
}
