#include "parsing.h"

t_red *ft_lstlast3(t_red *lst)
{
    if (!lst)
        return (NULL);
    while (lst->next != NULL)
    {
        lst = lst->next;
    }
    return (lst);
}

int ft_lstsize3(t_red *lst)
{
    t_red *temp;
    int i;

    temp = lst;
    i = 0;
    while (temp != NULL)
    {
        temp = temp->next;
        i++;
    }
    return (i);
}

void ft_lstadd_back3(t_red **lst, t_red *new)
{
    t_red *add;

    if (new)
    {
        if (!*lst)
        {
            *lst = new;
            new->next = NULL;
            return;
        }
        add = ft_lstlast3(*lst);
        add->next = new;
        new->next = NULL;
    }
}

t_red *ft_lstnew3(char *input, t_token token, char *file)
{
    t_red *newnode;

    newnode = malloc(sizeof(t_red));
    if (!newnode)
        return (NULL);
    newnode->input = ft_strdup(input);
    newnode->file = ft_strdup(file);
    newnode->token = token;
    newnode->next = NULL;
    return (newnode);
}

void creat_redirection(t_red **h, char *input, t_token token, char *file)
{
    t_red *new;

    if (*h == NULL)
    {
        printf("[1] %s\n --------------", file);
        *h = ft_lstnew3(input, token, file);
    }
    else
    {
        new = malloc(sizeof(t_red));
        new->input = ft_strdup(input);
         printf("[2] %s\n --------------", file);
        new->file = ft_strdup(file);
        new->token = token;
        new->next = NULL;
        ft_lstadd_back3(h, new);
    }
}