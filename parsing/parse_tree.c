#include "../parsing.h"

int check_pipe(t_list *last)
{
    while(last)
    {
        if(last->token == PIPE_LINE)
        {
            return (1);          
        }
        last = last->next;
    }
    return (0);
}

void    free_arr(char **arr)
{
    int i = 0;
    while(arr[i])
    {
        free(arr[i]);
        i++;
    }
    free(arr);
}

int     count_args(t_list *last)
{
    int count = 0;
    while(last && last->token != PIPE_LINE)
    {
        count++;
        last = last->next;
    }
    return (count);
}

void    check_parsing(t_list **last, t_ast *root)
{
    (void)root;
    t_list  *current = *last;
    char    **cmds;
    int     i = 0;
    int     count;
    
    while(current)
    {
        if(current->token == PIPE_LINE)
            current = current->next;
        else if(check_pipe(current))
        {
            count = count_args(*last);
            cmds = (char **)malloc(sizeof(char *) * count + 1);
            while(current && current->token != PIPE_LINE)
            {
                cmds[i] = ft_strdup(current->input);
                current = current->next;
                i++;
            }
            // here we gonna give the node in three the double array then free it
        }
        else
        {
            count = count_args(*last);
            while(current)
            {
                cmds[i] = ft_strdup(current->input);
                current = current->next;
                i++;
            }
        }
        current = current->next;
    }
    // for (int y; cmds[y]; y++)
    // {
    //     printf("%s\n", cmds[y]);
    // }
}