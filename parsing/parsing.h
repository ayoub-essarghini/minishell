#ifndef PARSING_H
#define PARSING_H

#include <stdio.h>
#include "./libft/libft.h"
#include <string.h>

typedef struct s_list
{
    char *input;
    char index;
    struct s_list *prev;
    struct s_list *next;
}t_list;



typedef struct s_line
{
    char **elem; // store elements
}

// ---->>>>>>>> PARSING FUNCTIONS 
void    store_map(char *line, t_list **list);
/// //// /  / / / / / / / / / / / / /

// --->>>>>>>>>>>>>>>> linked list
t_list	*ft_lstlast(t_list *lst);
int	    ft_lstsize(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	creat_nodes(t_list **head, char *input);
t_list	*ft_lstnew(char *input);

// // // // // // // // // // // // //

#endif 