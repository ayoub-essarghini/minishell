NAME = minishell
 
SRCS =  minishell.c \
		./parsing/ft_parse_line.c \
		./parsing/ft_split_line.c  pipe_exec.c \
		./parsing/linked_list.c \
		./parsing/check_concate.c \
		./parsing/check_commands.c \
		./parsing/utils.c export.c \
		here_doc_list.c redirections.c\
		execution.c envs_list.c change_dir.c \
		./parsing/parse_tree.c \


FLAGS = -Wall -Wextra -Werror 

LIBFT = ./parsing/libft/libft.a

GCC = cc

OBJS = $(SRCS:.c=.o)

INCLUDE = parsing.h ./parsing/libft/libft.h

.c.o:
	@$(GCC)  -c $< -o $@

$(NAME) : $(OBJS) $(INCLUDE)  
	@make -C ./parsing/libft
	@$(GCC) $(OBJS) $(LIBFT) -lreadline -o $(NAME) -g3 -fsanitize=address 
	@echo "done"


all: $(NAME) 

clean:
	@make clean -C ./parsing/libft
	@rm -f $(OBJS)
	 
fclean: clean
	@make fclean -C ./parsing/libft
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re