/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 16:51:26 by ssar              #+#    #+#             */
/*   Updated: 2021/06/02 15:35:05 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

static int	ft_inbase(char c)
{
	int		i;
	char	*base;

	base = "0123456789";
	i = 0;
	while (base[i])
	{
		if (c == base[i])
			return (i);
		i++;
	}
	return (-1);
}

static int	ft_space(char *str)
{
	int	i;

	i = 0;
	while ((str[i] > 8 && str[i] < 14) || str[i] == 32)
		i++;
	return (i);
}

unsigned int	ft_find_nbr(char *str, int i)
{
	int				a;
	unsigned int	nbr;

	a = 0;
	nbr = 0;
	while (a != -1)
	{
		a = ft_inbase(str[i]);
		if (a == -1)
			break ;
		nbr = nbr * 10 + a;
		i++;
	}
	return (nbr);
}

int	ft_atoi(char *str)
{
	int				i;
	int				neg;
	int				a;
	int				n;
	unsigned int	nbr;

	i = ft_space(str);
	neg = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg = -1;
		i++;
	}
	nbr = ft_find_nbr(str, i);
	if (neg < 0)
		return (n = nbr * neg);
	else
		return (nbr);
}
