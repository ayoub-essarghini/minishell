#include "parsing.h"

void echo_cmd(t_list *cmds, t_envs *envs)
{
    t_list *tmp = cmds->next;
    if (tmp)
    {
        if (ft_strcmp(tmp->input, "-n") == 0 && tmp->next != NULL)
        {
            while (tmp->next != NULL) // Check tmp->next before accessing tmp->next->input
            {
                if (tmp->next->input[0] != '$')
                {
                    printf("%s", tmp->next->input);
                    if (tmp->next)
                        printf(" ");
                }
                tmp = tmp->next;
            }
        }
        else
        {
            while (tmp)
            {
                printf("%s", tmp->input);
                if (tmp->next)
                    printf(" ");
                tmp = tmp->next;
            }
            printf("\n");
        }
    }
    else
        printf("\n");
}
char **conv_to_array(t_list *tab)
{
    int n = ft_lstsize(tab);
    char **arr = (char **)malloc(sizeof(char *) * n + 1);
    int i = 0;
    while (tab != NULL)
    {
        arr[i] = ft_strdup(tab->input);
        //   printf("%s\n",tab->input);
        tab = tab->next;
        i++;
    }
    arr[i] = NULL;
    return arr;
}

void exec_non_builtin(t_list *tab, t_envs **envs)
{
    int i = 0;
    char *error;
    char **args = conv_to_array(tab);
    char *get_path = get_myenv("PATH", &*envs);
    char **paths = ft_split(get_path, ':');

    pid_t pid = fork();
    if (pid == 0)
    {

        if (args[0][0] != '.')
        {

            // printf("is it a programme\n");
            if (ft_strcmp(args[0], "<<") != 0)
            {
                while (paths[i])
                {

                    char *new_cmd = ft_strjoin(paths[i], "/");
                    new_cmd = ft_strjoin(new_cmd, args[0]);
                    // printf("%s\n",new_cmd);
                    if (execve(new_cmd, args, NULL) == -1)
                    {
                        i++;
                    }
                    else
                    {
                        free(new_cmd);
                        return;
                    }
                    free(new_cmd);
                }
                perror(args[0]);
            }
        }
        else
        {

            if (execve(args[0], args, NULL) == -1)
            {
                perror(args[0]);
            }
        }
    }
    else
        wait(NULL);
}

void ft_exit(t_list *cmds)
{ 
    if (cmds->next != NULL)
    {
        int status = ft_atoi(cmds->next->input);
        if (status)
            exit(status);
        else
            exit(0);
    }
    else
        exit(0);
}

void exec_builtin(t_list *cmds, t_envs **envs)
{
    char *pwd;
    if (ft_strcmp(cmds->input, "env") == 0)
        get_export(NULL, NULL, &*envs);
    else if (ft_strcmp(cmds->input, "exit") == 0)
        ft_exit(cmds);
    else if (ft_strcmp(cmds->input, "export") == 0)
    {
        if (cmds->next == NULL || (cmds->next && ft_strcmp(cmds->next->input, "|") == 0))
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
    else if (ft_strcmp(cmds->input, "echo") == 0 || (cmds->next && ft_strcmp(cmds->next->input, "|") == 0))
        echo_cmd(cmds, *envs);
    else if (ft_strcmp(cmds->input, "cd") == 0)
        change_directory(cmds, &*envs);
    else if (cmds && ft_strcmp(cmds->input, "pwd") == 0)
    {
        pwd = get_myenv("PWD", &*envs);
        if (pwd)
            printf("%s\n", pwd);
    }
}
