NAME = minishell
CC = clang
FLAGS = -Wall -Werror -Wextra #-fsanitize=address
INC = -lncurses
SRCS = src/start/main.c \
       src/start/init.c \
       src/start/check_touch.c \
       src/start/arg_in_tab.c \
       src/start/arg_in_tab_b.c \
       src/start/read_cmd.c \
       src/start/execute.c \
       src/start/no_fork.c \
       src/start/my_readline_cur.c \
       src/redir/define_delimit.c \
       src/redir/ft_pipe.c \
       src/redir/get_redir_cur.c \
       src/redir/parse_red_env.c \
       src/redir/redir.c \
       src/redir/redir_b.c \
       src/redir/redir_current.c \
       src/redir/redir_current_b.c \
       src/redir/stock_redir.c \
       src/parser/lexing.c \
       src/parser/parsing.c \
       src/parser/utils_parsing.c \
       src/parser/utils_token.c \
       src/parser/start_parsing.c \
       src/manage_var/get_env.c \
       src/manage_var/env_in_tab.c \
       src/manage_var/utils_env.c \
       src/manage_var/modify_var_env.c \
       src/cmd/exit_com.c \
       src/cmd/exec_com.c \
       src/cmd/pwd_com.c \
       src/cmd/unset_com.c \
       src/cmd/env_com.c \
       src/cmd/cd_com.c \
       src/cmd/echo_com.c \
       src/cmd/export_com.c \
       src/cmd/history_com.c \
       src/utils/alloc_utils.c \
       src/utils/close_utils.c \
       src/utils/signal_handler.c \
       src/utils/ft_atoi.c \
       src/utils/cursor_position.c \
       src/utils/ft_itoa.c \
       src/utils/ft_bzero.c \
       src/utils/ft_split.c \
       src/utils/free_utils.c \
       src/utils/free_utils_b.c \
       src/utils/term_utils.c \
       src/utils/print_error.c \
       src/utils/other_utils.c \
       src/utils/list_basic_utils.c \
       src/utils/lst_basic_utils.c \
       src/utils/basic_utils.c \
       src/utils/str_utils.c \
       src/utils/put.c \
       src/fill_struct/split_command.c \
       src/fill_struct/fill_arguments.c \
       src/fill_struct/count_arg.c \
       src/fill_struct/count_letter_arg.c \
       src/fill_struct/count_utils.c \
       src/fill_struct/fill_utils.c \
       src/fill_struct/parse_utils.c \
       src/history/fleche_history.c \
       src/history/history.c \
       src/history/utils.c \
       src/history/write_history.c \
       src/history/clean_history.c \
       src/history/get_next_line.c
OBJS = $(SRCS:.c=.o)
$(NAME) : $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -I./includes -I./usr/include $(INC) -o $(NAME)
	#$(CC) $(FLAGS) $(OBJS) -I./includes -o $(NAME)
all : $(NAME)
clean : 
	rm -rf $(OBJS)
fclean : clean
	rm -rf $(NAME)
re : fclean all
