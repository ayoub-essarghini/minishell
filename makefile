NAME = minishell
 
SRCS =  minishell.c \
		./parsing/ft_parse_line.c ./parsing/ft_split_line.c \
		./parsing/check_concate.c ./parsing/tab_command.c \
		./parsing/parse_redir.c \
		./parsing/token.c \
		./linked_list_utils/linked_list1.c  ./linked_list_utils/linked_list.c \
		./linked_list_utils/redir_list.c ./linked_list_utils/tabcmd_list.c \
		./utils/utils.c ./utils/ft_split_line_utils.c ./utils/ft_split_quotes.c \
		./utils/check_syntax.c ./utils/utils_1.c ./utils/utils_2.c ./parsing/expand.c \
		./envs/zwa9.c ./execution/echo_cmd.c ./execution/pipe_exec_helper.c ./execution/pipe_exec_utils.c\
		./envs/env_list.c ./execution/redir_func.c ./execution/export_helper.c ./execution/chdir_utils.c\
		./envs/set_envs.c ./execution/exec_builtins.c ./execution/export_helper2.c ./execution/export_helper3.c \
		 ./execution/exec_simple_helper.c ./execution/signal_helper.c ./execution/exec_pipe_utils.c\
		./envs/get_env.c ./execution/exec_simple_cmd.c  ./execution/change_dir_helper.c \
		./execution/check_commands.c ./execution/ft_error.c ./execution/command_path.c\
		./execution/redirections.c  ./execution/pipe_exec.c ./execution/export.c \
		./execution/execution.c   ./execution/change_dir.c ./execution/ft_signals.c\

CFLAGS = -Wall -Wextra -Werror -g3 #-fsanitize=address 

LIBFT = ./libft/libft.a

GCC = cc

OBJS = $(SRCS:.c=.o)

INCLUDE = ./include/minishell.h ./include/parsing.h ./libft/libft.h

.c.o:
	@$(GCC)  -c $< -o $@

$(NAME) : $(OBJS) $(INCLUDE)  
	@make -C ./libft
	@$(GCC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -o $(NAME) 
	@echo "done"


all: $(NAME) 

clean:
	@make clean -C ./libft
	@rm -f $(OBJS)
	 
fclean: clean
	@make fclean -C ./libft
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re