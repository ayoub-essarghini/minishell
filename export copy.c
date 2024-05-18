#include "parsing.h"

char *ft_strncpy(char *dest, const char *src, size_t n)
{
    char *start = dest;
    while (*src && n--)
    {
        *dest++ = *src++;
    }
    // while (n--)
    // {
    //     *dest++ = '\0';
    // }
    return start;
}

char *get_value(char *str)
{
    size_t i;
    int j;
    char *value;

    i = 0;
    j = 0;
    while (str[i] && str[i] != '=')
        i++;
    if (!str[i])
        return (value);
    i++;
    while (str[i + j])
        j++;
    value = malloc((j + 1) * sizeof(char));
    if (!value)
        printf("allocation error\n");

    ft_strncpy(value, str + i, j);
    value[j] = '\0';

    return value;
}

char *get_key(char *str)
{
    size_t i;
    char *key;

    i = 0;
    while (str[i] && str[i] != '=')
        i++;
    key = malloc((i + 1) * sizeof(char));
    if (!key)
        printf("Memory allocation failed\n");

    ft_strncpy(key, str, i);
    key[i] = '\0';
    return key;
}

void print_env(t_envs **envs)
{
    t_envs *tmp;

    tmp = *envs;
    while (tmp)
    {
        printf("%s=\"%s\"\n", tmp->key, tmp->value);
        tmp = tmp->next;
    }
}

void get_export(char *key, char *value, t_envs **envs)
{
    if (!key && !value)
        print_env(&*envs);
    else
        creat_node(&*envs, key, value);
}

void set_export(t_list *cmds, t_envs **envs)
{
    t_list *tmp;
    char *key;
    char *value;

    tmp = cmds->next;
    while (tmp)
    {
        key = get_key(tmp->input);
        value = get_value(tmp->input);
        if (!key || !value)
            return;
        if (exist_env(key, &*envs) == 0)
            append_to_env(&*envs, key, value);
        else
            get_export(key, value, &*envs);
        tmp = tmp->next;
    }
}

void remove_env(t_list *cmds, t_envs **envs)
{
    t_list *tmp_cmd;
    char *key_to_remove;
    t_envs *tmp;
    t_envs *prev;
    t_envs *to_free;

    tmp_cmd = cmds->next;
    while (tmp_cmd)
    {
        key_to_remove = tmp_cmd->input;
        tmp = *envs;
        prev = NULL;

        while (tmp)
        {
            if (ft_strcmp(tmp->key, key_to_remove) == 0)
            {
                if (prev == NULL)
                    *envs = tmp->next;
                else
                    prev->next = tmp->next;
                to_free = tmp;
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
    t_envs *tmp;
    
    tmp = *envs;
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
