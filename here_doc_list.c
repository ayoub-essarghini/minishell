#include "parsing.h"


t_heredoc *ft_lstlast3(t_heredoc *lst)
{
    if (!lst)
        return (NULL);
    while (lst->next != NULL)
    {
        lst = lst->next;
    }
    return (lst);
}

int ft_lstsize3(t_heredoc *lst)
{
    t_heredoc *temp;
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

void ft_lstadd_back3(t_heredoc **lst, t_heredoc *new)
{
    t_heredoc *add;

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

t_heredoc *ft_lstnew3(char *input, char *delimiter)
{
    t_heredoc *newnode;

    newnode = malloc(sizeof(t_heredoc));
    if (!newnode)
        return (NULL);
    newnode->here_doc = strdup(input);
    newnode->delimiter= strdup(delimiter);
    newnode->next = NULL;
    return (newnode);
}

void creat_node3(t_heredoc **head, char *input, char *delimiter)
{
    t_heredoc *new;

    if (*head == NULL)
    {
        *head = ft_lstnew3(input,delimiter);
    }
    else
    {
        new = malloc(sizeof(t_heredoc));
        new->here_doc = ft_strdup(input);
        new->delimiter= ft_strdup(delimiter);
        new->next = NULL;
        ft_lstadd_back3(head, new);
    }
}