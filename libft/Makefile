# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abbouram <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/25 01:35:47 by abbouram          #+#    #+#              #
#    Updated: 2024/02/22 20:43:55 by abbouram         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =  ft_atoi.c \
	ft_itoa.c \
	ft_putendl_fd.c \
	ft_striteri.c \
	ft_strtrim.c \
	ft_bzero.c \
	ft_memchr.c \
	ft_putnbr.c \
	ft_strjoin.c \
	ft_substr.c \
	ft_calloc.c \
	ft_memcmp.c \
	ft_putnbr_fd.c \
	ft_strlcat.c \
	ft_tolower.c \
	ft_handle_format.c \
	ft_memcpy.c \
	ft_putstr.c \
	ft_strlcpy.c \
	ft_toupper.c \
	ft_isalnum.c \
	ft_memmove.c \
	ft_putstr_fd.c \
	ft_strlen.c \
	get_next_line.c \
	ft_isalpha.c \
	ft_memset.c \
	ft_put_unsigned.c \
	ft_strmapi.c \
	get_next_line_utils.c \
	ft_isascii.c \
	ft_printf.c \
	ft_split.c \
	ft_strncmp.c \
	ft_isdigit.c \
	ft_putchar.c \
	ft_strchr.c \
	ft_strnstr.c \
	ft_isprint.c \
	ft_putchar_fd.c \
	ft_strdup.c \
	ft_strrchr.c \
	ft_strcmp.c \
	ft_doubledup.c \
	ft_freedouble.c \
	ft_strlen_arr.c \

OBJS = ${SRCS:.c=.o}
NAME = libft.a
LIBC = ar rcs
INCLUDE = libft.h
CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror

.c.o:
	@${CC} ${CFLAGS} -c -fPIC $< -o ${<:.c=.o}

${NAME}: ${OBJS} $(INCLUDE)
	@${LIBC} ${NAME} ${OBJS}

all: ${NAME}

clean:
	@${RM} ${OBJS}

fclean: clean
	@${RM} ${NAME} 

re: fclean all

.PHONY : all clean fclean re
