#include "parsing.h"

void print_env(t_envs **envs)
{
    t_envs *tmp = *envs;
    while (tmp)
    {
        // printf("%s=%s\n", tmp->key, tmp->value);
        ft_putstr_fd(tmp->key,STDOUT_FILENO);
        ft_putstr_fd("=",STDOUT_FILENO);
        ft_putstr_fd(tmp->value,STDOUT_FILENO);
        ft_putstr_fd("\n",STDOUT_FILENO);
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
        creat_node(&*envs, key, value);
    }
}

void set_export(t_list *cmds, t_envs **envs)
{
    t_list *tmp = cmds->next;
    while (tmp)
    {
        char *key = get_key(tmp->input);
        char *value = get_value(tmp->input);
        if (exist_env(key, &*envs) == 0)
            append_to_env(&*envs, key, value);
        else
            get_export(key, value, &*envs);
        tmp = tmp->next;
    }
}

void remove_env(t_list *cmds, t_envs **envs)
{
    t_list *tmp_cmd = cmds->next;

    while (tmp_cmd)
    {
        char *key_to_remove = tmp_cmd->input;
        t_envs *tmp = *envs;
        t_envs *prev = NULL;

        while (tmp)
        {
            if (strcmp(tmp->key, key_to_remove) == 0)
            {
                if (prev == NULL)
                    *envs = tmp->next;
                else
                    prev->next = tmp->next;
                t_envs *to_free = tmp;
                tmp = tmp->next;
                free(to_free);
            }
            else
            {
                prev = tmp;
                tmp = tmp->next;
            }
        }
        tmp_cmd = tmp_cmd->next;
    }
}
int exist_env(char *key, t_envs **envs)
{
    t_envs *tmp = *envs;
    while (tmp)
    {
        if (ft_strcmp(tmp->key, key) == 0)
            return (0);
        tmp = tmp->next;
    }
    return (-1);
}
void set_defautl_env(t_envs **envs)
{
    char *data[] = {"PWD=/Users/aes-sarg/minishell", "SHLVL=1", "_=/usr/bin/env", NULL};
    set_envs(data, &*envs);
}

void append_to_env(t_envs **envs, char *key, char *value)
{
    t_envs *tmp = *envs;
    t_envs *prev = NULL;
    while (tmp)
    {
        if (ft_strcmp(tmp->key, key) == 0)
        {
            if (prev == NULL)
                *envs = tmp->next;
            else
                prev->next = tmp->next;
            t_envs *to_free = tmp;
            tmp = tmp->next;
            free(to_free);
        }
        else
        {
            prev = tmp;
            tmp = tmp->next;
        }
    }
    creat_node(envs, key, value);
}
