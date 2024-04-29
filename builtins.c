#include "parsing.h"

void print_env(t_envs *envs)
{
    char *key;
    char *value;

    while (envs)
    {
        key = get_key(envs->key);
        value = get_value(envs->value);
        printf("%s=%s\n", key, value);
        envs = envs->next;
    }
}

void get_export(char *key, char *value, t_envs **envs)
{
    if (!key && !value)
    {
        // print_env(envs);
    }
    else
    {
        creat_node(&envs,key,value);
    }
}
void set_defautl_env(t_envs **envs)
{
    char *data[] = {"PWD=/Users/aes-sarg/minishell","SHLVL=1","_=/usr/bin/env",NULL};
    set_envs(data,envs);
}