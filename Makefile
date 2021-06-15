NAME = minishell
CC = clang
FLAGS = -Wall -Werror -Wextra #-fsanitize=address
INC = -lreadline
SRCS = src/start/main.c \
       src/start/init.c \
       src/start/arg_in_tab.c \
       src/start/arg_in_tab_b.c \
       src/start/read_cmd.c \
       src/start/execute.c \
       src/start/redir.c \
       src/start/redir_b.c \
       src/start/ft_pipe.c \
       src/start/no_fork.c \
       src/start/redir_current.c \
       src/start/get_redir_cur.c \
       src/start/my_readline_cur.c \
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
       src/utils/alloc_utils.c \
       src/utils/close_utils.c \
       src/utils/signal_handler.c \
       src/utils/ft_atoi.c \
       src/utils/ft_itoa.c \
       src/utils/ft_split.c \
       src/utils/free_utils.c \
       src/utils/print_error.c \
       src/utils/other_utils.c \
       src/utils/list_basic_utils.c \
       src/utils/lst_basic_utils.c \
       src/utils/basic_utils.c \
       src/parse/split_command.c \
       src/parse/check_syntax_un.c \
       src/parse/check_syntax_deux.c \
       src/parse/fill_arguments.c \
       src/parse/count_arg.c \
       src/parse/count_letter_arg.c \
       src/parse/count_utils.c \
       src/parse/fill_utils.c \
       src/parse/parse_utils.c 
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
