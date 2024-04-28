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

void exec_builtin(t_list *cmds, t_envs *envs)
{
   if (ft_strcmp(cmds->input,"env") == 0)
   {
    while (envs != NULL)
    {
       printf("%s",envs->key);
       envs = envs->next;
    }

    printf("it working as well");
   }
 
}

