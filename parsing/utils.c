#include "../parsing.h"

void    print_nodes(t_list *tab)
{
    int i = 1;
    while(tab)
    {
        printf("[%d]->$%s$\n", i, tab->input);
        if(tab->token == WORD)
        printf("   ->WORD\n");
        if(tab->token == OPTION)
        printf("   ->OPTION\n");
        if(tab->token == ENV)
        printf("   ->ENV\n");
        if(tab->token == PIPE_LINE)
        printf("   ->PIPE_LINE\n");
        if(tab->token == REDIR_IN)
        printf("   ->REDIR_IN\n");
        if(tab->token == REDIR_OUT)
        printf("   ->REDIR_OUT\n");
        if(tab->token == HERE_DOC)
        printf("   ->HERE_DOC\n");
        if(tab->token == APPEND)
        printf("   ->APPEND\n");
        tab = tab->next;
        i++;
    }
}

void    ft_free(t_list *tab)
{
    t_list *temp;
    
    if(tab)
    {
        while (tab != NULL)
        {
                temp = tab;
                tab = tab->next;
                free(temp->input);
                if(temp)
                    free(temp);
        }
    }
}

void    ft_error(t_list *tab)
{
    ft_free(tab);
    tab = NULL;
    ft_putendl_fd("error", 2);
    exit(0);
}
