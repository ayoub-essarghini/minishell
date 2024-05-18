#include "../parsing.h"

void    print_nodes(t_list *tab)
{
    int i = 1;
    while(tab)
    {
        printf("NODE[%d]<->Status[%d]-->$%s$\n", i,tab->status, tab->input);
        if(tab->token == WORD)
        printf("   ->WORD\n");
        if(tab->token == OPTION)
        printf("   ->OPTION\n");
        if(tab->token == WHITE_SPACE)
        printf("   ->WHITE_SPACE\n");
        if(tab->token == ENV)
        printf("   ->ENV\n");
        if(tab->token == PIPE_LINE)
        printf("   ->PIPE_LINE\n");
        if(tab->token == REDIR_IN)
        printf("   ->REDIR_IN\n");
        if(tab->token == REDIR_OUT)
        printf("   ->REDIR_OUT\n");
        if(tab->token == QUOTES_SPACES)
        printf("   ->QUOTES_SPACES\n");
        if(tab->token == CONCATED)
        printf("   ->CONCATED\n");
        if(tab->token == REDIR_APPEND)
        printf("   ->REDIR_APPEND\n");
        if(tab->token == HERE_DOC)
        printf("   ->HERE_DOC\n");
        if(tab->token == NOT_DEF)
        printf("   ->NOT_DEF\n");
        tab = tab->next;
        i++;
    }
}

int all_alpha(char *str)
{
    int i = 0;
    while (str[i])
    {
        if (!((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z')))
            return (0);
        i++;
    }
    return (1);
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

int    all_space(char *str)
{
    int i;

    i = 0;
    while(str[i] == ' ' || str[i] == '\t')
    i++;
    if(str[i] == '\0')
        return (0);
    return (1);
}

int    check_line(char *str)
{
    int check = ft_strcmp(str, "exit");
    if(!check)
    {
        exit(0);
    }
    if(!all_space(str) || (ft_strcmp(str, "")) == 0)
    {
        return (1);
    }
    return (0);
}
