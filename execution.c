#include "parsing.h"

int exec_builtin(t_list *cmds)
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
            char *cmd = ft_strjoin(arr[i], "/");

            cmd = ft_strjoin(cmd, cmds->input);
            // cmd = ft_strjoin(cmd, " -la");
            char **tt = ft_split(cmd, ' ');
            if (execve(cmd, tt, NULL) == -1)
            {
                i++;
            }
            else
            {  
                return 0;
                // break;
            }
           
        }
    }
  return (-1);

}