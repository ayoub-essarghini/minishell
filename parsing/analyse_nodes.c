#include "../parsing.h"

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

int check_quotes(t_list *tab)
{
    int count = 0;
    int i = 0;

    while (tab)
    {
        while (tab->input[i])
        {
            if (tab->input[i] == '"' && tab->input[i - 1] == '\\')
                i++;
            else if (tab->input[i] == '"')
                count += 1;
        }
    }
    if (count % 2 == 0)
        return (1);
    return (0);
}

void check_nodes(t_list *tab)
{
    while (tab)
    {
        if (all_alpha(tab->input))
            tab->token = WORD;
        else if (!all_alpha(tab->input) && tab->input[0] == '-')
        {
            if(!all_alpha(tab->input) && tab->input[0] == '-')
            {
                
            }

        }
        else if (!all_alpha(tab->input) && tab->input[0] == '$')
            tab->token = ENV;
        else if (strcmp(tab->input, "|") == 0)
            tab->token = PIPE_LINE;
        else if (strcmp(tab->input, "<") == 0)
            tab->token = REDIR_IN;
        else if (strcmp(tab->input, ">") == 0)
            tab->token = REDIR_OUT;

        tab = tab->next;
    }
}

void check_first(t_list *tab, t_envs *envs)
{
    int i;
    char *builtins[] = {"echo", "pwd", "export", "unset", "env", "exit", NULL};

    i = 0;
    if (tab->token == WORD)
    {
        while (builtins[i])
        {
            if (ft_strcmp(tab->input, builtins[i]) == 0)
            {
             exec_builtin(tab,envs);
            }

            i++;
        }
    }
  
}