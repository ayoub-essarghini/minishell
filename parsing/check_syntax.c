#include "parsing.h"

int     check_quotes(char *str)
{
    char c;
    int     i;
    while(str[i])
    {
        if(str[i] == '\'' || str[i] == '"')
        {
            c = str[i]; 
            while(str[i])
            {
                if(str[i] == c)
                return (1);
            }
            ++i;
        }
        i++;
    }
    return (0);
}

int     check_redirections(t_list *tab)
{
    if(tab->token == HERE_DOC || tab->token == REDIR_IN
        || tab->token == REDIR_OUT || tab->token == REDIR_APPEND)
        {
            
        }
}

int     check_syntax(t_list *tab)
{
    while(tab)
    {
       if(check_redirections(tab))
       {
            
       }
       if(tab->token == PIPE_LINE)
       {
            
       }
    }
}

