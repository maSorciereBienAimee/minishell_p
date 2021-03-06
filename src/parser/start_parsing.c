/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nayache <nayache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 15:45:13 by nayache           #+#    #+#             */
/*   Updated: 2021/06/24 16:14:15 by nayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer_parser.h"
#include <stdlib.h>

int	start_parsing(char *str)
{
	t_token	*token;

	token = init_token(NULL);
	if (str == NULL || token == NULL)
		return (-1);
	if (lexing(str, token) == -1 || parsing(token) == -1)
	{
		free_token(token);
		return (-1);
	}
	free_token(token);
	return (0);
}
