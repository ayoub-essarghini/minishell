#include "parsing.h"

void echo_cmd(t_list *cmds)
{
    t_list *tmp = cmds->next;
    if (ft_strcmp(tmp->input, "-n") == 0 && tmp->next != NULL)
    {
        while (tmp->next != NULL) // Check tmp->next before accessing tmp->next->input
        {
            printf("%s", tmp->next->input);
            if (tmp->next->next != NULL)
                printf(" ");
            tmp = tmp->next;
        }
    }
    else
    {
        while (tmp)
        {
            printf("%s", tmp->input);
            if (tmp->next != NULL)
                printf(" ");
            tmp = tmp->next;
        }
        printf("\n");
    }
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

// }

void exec_builtin(t_list *cmds, t_envs **envs)
{

    if (ft_strcmp(cmds->input, "env") == 0)
    {
        get_export(NULL, NULL, &*envs);
    }
    else if (ft_strcmp(cmds->input, "export") == 0)
    {
        if (cmds->next == NULL)
            get_export(NULL, NULL, &*envs);
        else
            set_export(cmds, &*envs);
    }
    else if (ft_strcmp(cmds->input, "unset") == 0)
    {
        if (cmds->next != NULL)
            remove_env(cmds, &*envs);
        else
            printf("unset : not enough arguments\n");
    }
    else if (ft_strcmp(cmds->input, "echo") == 0)
    {
        echo_cmd(cmds);
    }
}
