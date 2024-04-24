NAME = minishell
 
SRCS =  minishell.c \
		check_line.c \
		get_line.c \
		linked_list.c \
		utils.c \
		analyse_nodes.c \

FLAGS = -Wall -Wextra -Werror 

LIBFT = ./libft/libft.a

GCC = cc

OBJS = $(SRCS:.c=.o)

INCLUDE = parsing.h ./libft/libft.h

.c.o:
	@$(GCC) $(FLAGS) -c $< -o $@

$(NAME) : $(OBJS) $(INCLUDE)  
	@make -C ./libft
	@$(GCC) $(OBJS) $(LIBFT) -lreadline $(FLAGS) -o $(NAME)
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