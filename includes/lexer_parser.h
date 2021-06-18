/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_parser.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nayache <nayache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 15:14:30 by nayache           #+#    #+#             */
/*   Updated: 2021/06/17 19:08:54 by nayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_PARSER_H
# define LEXER_PARSER_H

# define BACKSLASH '\\'
# define QUOTE '\''
# define DQUOTE '"'
# define DIRIN '<'
# define DIROUT '>'
# define PIPE '|'
# define DOLLAR '$'
# define QUEST '?'
# define EQUAL_ASSIGN '='
# define END_CMD ';'

typedef enum	e_tokentype
{
	Text,
	Whitespace,
	Dirin,
	Dirout,
	Pipe,
	End_cmd,
	Escape,
	Quote_text,
	Dquote_text
}				t_tokentype;

typedef	enum	e_state
{
	START,
	EAT,
	INPUT,
	OUTPUT,
	FLUX,
	ERROR
}				t_state;

typedef struct	s_token
{
	t_tokentype		type;
	char			*data;
	struct s_token	*prev;
	struct s_token	*next;
}				t_token;

int				start_parsing(char *str);
int				lexing(char *buf, t_token *token);
int				parsing(t_token *token);
void			ft_putstr(char *str);
void			ft_putstr_fd(char *str, int fd);
int				is_space(char c);
int				is_text(char c);
t_tokentype		get_type(char c);
int				check_special_char(char c);
t_token			*get_last_token(t_token *token);
t_token			*init_token(char *insert);
void			lst_push_back(t_token *list, t_token *neew);
int				add_token(t_token *list, char *item, char first, int size);
void			free_token(t_token *list);
char			*ft_strdup(const char *src);
int				ft_strlen(const char *str);
char			*ft_strchr(const char *str, int c);
char			*ft_strjoin(const char *s1, const char *s2);

#endif
