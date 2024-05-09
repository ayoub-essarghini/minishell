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
        else if (!all_alpha(tab->input) && tab->input[0] == '$')
            tab->token = ENV;
        else if (strcmp(tab->input, "|") == 0)
            tab->token = PIPE_LINE;
        else if (strcmp(tab->input, "<") == 0)
            tab->token = REDIR_IN;
        else if (strcmp(tab->input, ">") == 0)
            tab->token = REDIR_OUT;
        else if (strcmp(tab->input, "<<") == 0)
            tab->token = HERE_DOC;
        else if (strcmp(tab->input, ">>") == 0)
            tab->token = APPEND;

        tab = tab->next;
    }
}

int is_builtin(char *cmd)
{
    int i;
    char *builtins[] = {"echo", "cd", "pwd", "export",
                        "unset", "env", "exit", NULL};

    i = 0;
    while (builtins[i])
    {
        if (ft_strcmp(cmd, builtins[i]) == 0)
            return (0);
        i++;
    }
    return (-1);
}

int exist_pipe(t_list *tab)
{
    t_list *tmp = tab;
    while (tmp)
    {
        if (ft_strcmp(tmp->input, "|") == 0)
        {
            return 0;
        }
        tmp = tmp->next;
    }
    return (-1);
}

int n_herdoc(t_list *cmds)
{
    t_list *tmp = cmds;
    int i = 0;
    while (tmp)
    {
        i++;
      tmp = tmp->next;
    }
    return (i);
}

int exist_here_doc(t_list *tab)
{
    t_list *tmp = tab;
    while (tmp)
    {
        if (ft_strcmp(tmp->input, "<<") == 0)
        {
            return 0;
        }
        tmp = tmp->next;
    }
    return (-1);
}

void check_first(t_list *tab, t_envs *envs)
{

    if (tab->token == WORD  || tab->token == HERE_DOC || tab->token == PIPE_LINE)
    {
        if (exist_pipe(tab) == -1)
        {
            if (is_builtin(tab->input) == 0)
                exec_builtin(tab, &envs);
            else
            {
                if (exist_here_doc(tab) == 0)
                {
                    t_list *tmp = tab;
                    while (tmp)
                    {
                       if (tmp->token == HERE_DOC && tmp->next)
                       {
                        open_heredoc(tmp->input,tmp->next->input);
                       }
                       tmp = tmp->next;
                    }

                    char *args[] = {"/bin/ls", "-la", NULL};
                    if (execve(args[0],args,NULL) == -1)
                    {
                            perror("ls");
                    }
                  
                    
                }
                else
                {
                    exec_non_buitin(tab, &envs);
                }

            }
        }
        else
            exec_with_pipeline(tab, &envs);
    }
    else if (tab->token == ENV)
    {
        char *str = get_myenv(tab->input + 1, &envs);
        if (str)
            printf("%s\n", str);
    }
    // else if (tab && tab->token == HERE_DOC)
    // {
    //     handle_here_doc(tab,envs);
     
        
    // }
}
