NAME = minishell
 
SRCS =  minishell.c \
		./parsing/check_line.c \
		./parsing/get_line.c \
		./parsing/linked_list.c \
		./parsing/utils.c \
		./parsing/analyse_nodes.c \
		execution.c

FLAGS = -Wall -Wextra -Werror 

LIBFT = ./parsing/libft/libft.a

GCC = cc

OBJS = $(SRCS:.c=.o)

INCLUDE = parsing.h ./parsing/libft/libft.h

.c.o:
	@$(GCC) $(FLAGS) -c $< -o $@

$(NAME) : $(OBJS) $(INCLUDE)  
	@make -C ./parsing/libft
	@$(GCC) $(OBJS) $(LIBFT) -lreadline $(FLAGS) -o $(NAME) -fsanitize=address
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