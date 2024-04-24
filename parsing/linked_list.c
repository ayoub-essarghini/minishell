#include "parsing.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

int	ft_lstsize(t_list *lst)
{
	t_list	*temp;
	int		i;

	temp = lst;
	i = 0;
	while (temp != NULL)
	{
		temp = temp->next;
		i++;
	}
	return (i);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*add;

	add = ft_lstlast(*lst);
	add->next = new;
	new->prev = add;
	new->next = NULL;
}

void	creat_nodes(t_list **head, char *input, int status)
{
	t_list	*new;

	if (*head == NULL)
	{
		*head = ft_lstnew(input, status);
	}
	else
	{
		new = malloc(sizeof(t_list));
		new->input = ft_strdup(input);
		new->status = status;
		new->prev = NULL;
		new->next = NULL;
		ft_lstadd_back(head, new);
	}
}

t_list	*ft_lstnew(char *input, int status)
{
	t_list	*newnode;

	newnode = malloc(sizeof(t_list));
	if (!newnode)
		return (NULL);
	newnode->input = ft_strdup(input);
	newnode->status = status;
	newnode->next = NULL;
	newnode->prev = NULL;
	return (newnode);
}
