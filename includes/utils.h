/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 23:04:30 by ssar              #+#    #+#             */
/*   Updated: 2021/06/29 16:07:55 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include "history.h"
# include "minishell.h"

typedef struct s_actual
{
	char			**str_arg;
	char			**str_wenv;
	int				arg_command;
	int				pipe;
	int				append;
	int				redir_out;
	int				redir_cur;
	int				redir_in;
	int				no_suite;
	struct s_actual	*next;
}			t_actual;

typedef struct s_arg_redir
{
	struct s_arg_redir	*prev;
	char				**str;
	struct s_arg_redir	*next;
}		t_arg_redir;

typedef struct s_redir_cur
{
	int					j;
	struct s_arg_redir	*arg;
	struct s_redir_cur	*next;
}		t_redir_cur;

typedef struct s_list_env
{
	char				*name;
	char				*value;
	int					equal;
	struct s_list_env	*next;
}				t_list_env;

typedef struct s_sh
{
	int				no_env;
	int				tty_col;
	int				tty_row;
	int				init_cursor_r;
	int				init_cursor_c;
	struct termios	old_tty;
	struct termios	new_tty;
	int				in_read;
	int				parent;
	int				save_stdout;
	int				code;
	char			*path;
	int				exit;
	int				i;
	int				last_exit;
	char			*result;
	t_list_env		*var_env;
	char			**tab_env;
	int				size_path;
	int				alloue[15];
	int				fd_pipe[2];
	int				fd_redir[2];
	int				fd_in;
	int				fd_out;
	char			*command;
	char			**spl;
	int				end_cmd;
	pid_t			fils_pid;
	int				read_pipe;
	int				ready;
	int				stop;
	int				test_exec;
	int				if_redir_cur;
	char			*home_path;
	char			*pwd_path;
	t_redir_cur		*redir;
	t_redir_cur		*stock_redir;
	t_arg_redir		*stock_redir_arg;
	t_actual		*actu;
	t_actual		*stock_actu;
	t_actual		*stock_for_pipe;
	t_hist			*history;
}				t_sh;

void		ft_putchar(char c);
void		ft_putnbr(int n);
void		ft_putstr(char *str);
void		ft_putstr_fd(char *str, int fd);
int			ft_putchar_b(int c);
char		*my_realloc(t_sh *sh, char *buff, int i);
void		my_exit(t_sh *sh, char *w);
void		ft_error(t_sh *sh, char *str, char *cmd, char *pb);
void		ft_error_cmd(t_sh *sh, char *str, char *cmd, int i);
char		*stock_tab(t_sh *sh, char *my_tab, int i);
int			ft_comp(char *str, char *str2);
int			ft_in(char c, char *str);
int			ft_atoi(char *str);
char		*which_command(t_sh *sh, char *str);
int			num_of_args(t_sh *sh);
int			arg_is_invalid(char *arg);
char		*get_first_arg(t_sh *sh, char *str);
void		my_free(t_sh *sh);
void		print_error_inv_arg(t_sh *sh, char *str, char **lst);
void		print_error_too_arg(t_sh *sh, char *str, char **lst);
int			ft_len(char *str);
int			ft_len_list(t_list_env *var);
char		**ft_split_commande(t_sh *sh, char *s, char c);
char		*ft_free_tab(char **ptr);
void		check_if_in_quote(int i, char *s, int *q);
void		ft_free_list(t_list_env **lst);
t_list_env	*ft_lstlast(t_list_env *lst);
void		lst_add_back(t_list_env **last, t_list_env *newlst);
char		*copy_char(t_sh *sh, char *dest, char *source);
void		ft_swap(char **s1, char **s2);
char		*ft_itoa(int n);
char		*get_lst_value_of(t_sh *sh, char *name);
void		check_back_slash(int *i, char *c, int j, int *dsb);
void		fill_arg_cmd(t_sh *sh, char *spl, int i, char **to_fill);
int			is_al_num(char c);
int			end_arg(char *spl, int i, int *q);
int			error_quote( char c);
int			check_parenthese(char c, int *dsb);
int			is_error_syntax(t_sh *sh, char *s, int i, char *err);
int			check_format_pipe(t_sh *sh, char **ptr);
int			check_format_global(t_sh *sh, char *s);
int			check_format_virgule(t_sh *sh, char *s);
void		sort_tab_env(t_sh *sh, char **tableau);
void		init_meta(t_actual *ptr);
int			is_al_num(char c);
void		ft_free_lst_cmd(t_actual **lst);
void		lst_add_back_cmd(t_actual **last, t_actual *new_lst);
void		execute_cmd(t_sh *sh, char *spl);
int			manage_redir(t_sh *sh, char *spl);
t_actual	*ft_lstlast_cmd(t_actual *lst);
void		echo_command(t_sh *sh, char *spl, t_actual *actu, char **arg);
char		**ft_split(char const *s, char c);
void		launch_exec(t_sh *sh, char *spl, char *word, char **list_arg);
void		boucle_minishell(t_sh *sh, char *spl);
void		is_it_pipe(t_sh *sh, char *spl);
void		skip_space(char *spl, int *i);
void		handler_sigint(int sig);
void		handler_sigquit(int sig);
char		**all_arg(t_sh *sh);
int			manage_redir_b(t_sh *sh, char *spl, t_actual *temp, t_actual *stok);
char		**all_arg_b(t_sh *sh, t_actual *stock);
int			copy_arg(char **dest, char **src);
void		continue_parent(t_sh *sh, pid_t pid);
void		modify_env(t_sh *sh, char **lst, int exp);
int			verify_name(t_sh *sh, char *name, char *group, char *cmd);
int			check_form_redir_in(t_sh *sh, char *s, int *i, int *dsb);
int			is_name_eq_value(char *str);
void		print_env(t_sh *sh);
char		*get_name(t_sh *sh, char *str);
char		*get_value(t_sh *sh, char *str);

void		lst_add_back_red(t_redir_cur **last, t_redir_cur *new_lst);
void		ft_free_list_arg_redir(t_arg_redir **lst);
void		lst_add_back_arg_red(t_arg_redir **last, t_arg_redir *new_lst);
t_arg_redir	*ft_lstlast_arg_redir(t_arg_redir *lst);
char		**get_redir_arg(t_sh *sh, char *word, int stop);
char		*my_readline(t_sh *sh);
void		get_redir_cur(t_sh *sh);
void		continue_boucle_cl(char *spl, int *dsb, int *i);
int			which_case_count(char *s, int *j, int *dsb);
int			var_exit_status(t_sh *sh, int *i);
int			which_case(char *s, int *ij, int *dsb);
void		init_for_fill(char *spl, int *dsb, int *ij, int i);
void		end_fill_arg(char *s, int *ij, int *d, char **to_fill);
void		case_exit_status(t_sh *sh, int *ij, char **to_fill);
int			debut_fill_arg(char *s, int *ij, int *d);
void		suite_redir(t_sh *sh);
int			is_pipe(t_sh *sh, t_actual *temp);
int			redir_current_b(t_sh *sh, char *spl, t_actual *ac, t_actual *sto);
void		redir_current(t_sh *sh, char *spl);
void		ft_bzero(void *s, size_t n);
void		pass_non_canonique(t_sh *sh);
void		fleche_bas(t_sh *sh);
void		fleche_haut(t_sh *sh);
void		history_command(t_sh *sh, char **lst_arg, t_actual *actu);
int			get_cursor(t_sh *sh, int *rc, int del);
char		*parse_delimiteur(t_sh *sh, char *str);
int			count_letter_env(t_sh *sh, char *spl, int *i);
void		case_env(t_sh *sh, int *ij, char *s, char **to_fill);
void		parse_redir(t_sh *sh, char *word, char **stock);
void		my_exit_final(t_sh *sh);
int			check_touche(t_sh *sh, char *b, int *j, int *i);
char		*copy_end_char(t_sh *sh, char *spl, int count, int i);
void		ft_free_list_red(t_redir_cur **lst);

#endif
