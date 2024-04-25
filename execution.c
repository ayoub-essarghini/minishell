#include "parsing.h"

void echo_cmd(char *option, char *message)
{
        if (strcmp(option , "") == 0)
        {
            printf("%s\n",message);
        }
        else
            printf("%s",message);
}
void    pwd_cmd()
{
    char *pwd = getenv("PWD");
    printf("%s\n",pwd);
}
void exec_cmd_with_option(t_list *tab)
{
    if (strcmp(tab->input, "echo") == 0)
    {
        echo_cmd("-n","hello");
    }
}
// }

void exec_builtin(t_list *cmds)
{
    pid_t pid = fork();
    if (pid == 0)
    {
        (void)cmds;
        char *s = getenv("PATH");
        char **arr = ft_split(s, ':');
        int i = 0;
        while (arr[i] != NULL)
        {
            printf("%s\n",arr[i]);
            // char *cmd = ft_strjoin(arr[i], "/");
            // cmd = ft_strjoin(cmd, cmds->input);
            // // cmd = ft_strjoin(cmd, " -la");
            // char **tt = ft_split(cmd, ' ');
            // execve(cmd, tt, NULL);
            i++;
        }
    }
    else
    {
        wait(NULL);
    }
 
}

