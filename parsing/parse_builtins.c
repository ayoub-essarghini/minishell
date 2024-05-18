#include "parsing.h"

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




void    check_builtins(t_list *cmds)
{






}


