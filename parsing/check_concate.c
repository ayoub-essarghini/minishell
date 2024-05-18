#include "../parsing.h"

int calcul_nodes(t_list *tab)
{
    int count = 0;
    while (tab && tab->token != WHITE_SPACE && tab->token != HERE_DOC && tab->token != REDIR_APPEND
                && tab->token != REDIR_IN && tab->token != REDIR_OUT && tab->token != PIPE_LINE)
    {
        count++;
        tab = tab->next;
    }
    return (count);
}

void ft_check_concate(t_list **tab, t_list **last)
{
    t_list *current = *tab;
    char *concate = "";
    t_list *tmp;

    while (current)
    {
        if (current->token != WHITE_SPACE && current->token != HERE_DOC && current->token != REDIR_APPEND 
            && current->token != REDIR_IN && current->token != REDIR_OUT 
            && current->token != PIPE_LINE && calcul_nodes(current) > 1)
        {
            while (current && current->token != WHITE_SPACE && current->token != HERE_DOC 
                    && current->token != REDIR_APPEND && current->token != REDIR_IN 
                    && current->token != REDIR_OUT && current->token != PIPE_LINE)
            {
                tmp = current;
                concate = ft_strjoin(concate, current->input);
                current = current->next;
                free(tmp);
            }
            creat_last(last, concate, CONCATED, 0);
            free(concate);
        }
        else if(current->token == WHITE_SPACE)
        {    
            tmp = current;
            current = current->next;
            free(tmp);
        }
        else if(current->token != HERE_DOC && current->token != REDIR_APPEND && current->token != REDIR_IN 
                && current->token != REDIR_OUT && current->token != PIPE_LINE)
        {
            tmp = current;
            creat_last(last, current->input, current->token, current->status);
            current = current->next;
            free(tmp);
        }
        else
        {
            tmp = current;
            creat_last(last, current->input, current->token, current->status);
            current = current->next;
            free(tmp);
        }
        
    }
}
