#include "parsing.h"

void print_env(t_envs **envs)
{
t_envs *tmp = *envs;
    while (tmp)
    {
        printf("%s=%s\n",tmp->key,tmp->value);
        tmp = tmp->next;
    }
    
}

void get_export(char *key, char *value, t_envs **envs)
{
    if (key == NULL && value == NULL)
    {
        print_env(&*envs);
        // printf("all is ready\n");
    }
    else
    {
        creat_node(&*envs,key,value);
    }
}
void set_defautl_env(t_envs **envs)
{
    char *data[] = {"PWD=/Users/aes-sarg/minishell","SHLVL=1","_=/usr/bin/env",NULL};
    set_envs(data,&*envs);
}