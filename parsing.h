#ifndef PARSING_H
#define PARSING_H

#include "minishell.h"
#include <stdio.h>
#include "./parsing/libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <string.h>

typedef enum s_state
{
    Single = 1,
    Double = 2,
    General = 0
} state;

typedef enum e_token
{
	WORD,
	WHITE_SPACE,
	OPTION,	
	NEW_LINE,
	QOUTE,
	DOUBLE_QUOTE,
	ESCAPE,
	ENV,
	PIPE_LINE,
	REDIR_IN,
	REDIR_OUT,
	HERE_DOC,
	DREDIR_OUT,
} t_token;

typedef struct s_list
{
    char    *input;
    state   status;
    t_token token;
    struct s_list *next;
    struct s_list *prev;
}t_list;

//  PARSING 

int    check_line(char *str);
void	get_line(t_list **tab, char *line);
void    check_nodes(t_list *tab);
void    check_first(t_list *tab);
void exec_builtin(t_list *cmds);

// linked list
t_list	*ft_lstlast(t_list *lst);
int	    ft_lstsize(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	creat_nodes(t_list **head, char *input, int status);
t_list	*ft_lstnew(char *input, int status);
void exec_cmd_with_option(t_list *tab);

// utils

void    print_nodes(t_list *tab);
void    ft_free(t_list *tab);
void    ft_error(t_list *tab);

#endif 