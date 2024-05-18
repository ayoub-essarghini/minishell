#include "../parsing.h"

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

void check_node(t_list *tab, t_envs *envs)
{



    // if (exist_pipe(tab) == -1)
    // {
    //     if (is_builtin(tab->input) == 0)
    //         exec_builtin(tab, &envs);
    //     else
    //         exec_non_buitin(tab, &envs);
    // }
    // else
    //     exec_with_pipeline(tab, &envs);

    execute_command_with_redirection(tab,&envs);
}