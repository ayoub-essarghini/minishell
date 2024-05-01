#include "parsing.h"

void echo_cmd(t_list *cmds)
{

    t_list *tmp = cmds->next;
    if (tmp)
    {
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
void exec_non_buitin(t_list *tab, t_envs **envs)
{
    int i = 0;
    char *error;
    char **args = conv_to_array(tab);
    char *get_path = get_myenv("PATH", &*envs);
    char **paths = ft_split(get_path, ':');

    pid_t pid = fork();

    if (pid == 0)
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
    else
        wait(NULL);
}

void exec_builtin(t_list *cmds, t_envs **envs)
{

    if (ft_strcmp(cmds->input, "env") == 0)
        get_export(NULL, NULL, &*envs);
    else if (ft_strcmp(cmds->input, "exit") == 0)
        exit(0);
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
        echo_cmd(cmds);
    else if (ft_strcmp(cmds->input, "cd") == 0)
        change_directory(cmds, &*envs);
    else if (ft_strcmp(cmds->input, "pwd") == 0)
    {
        char *pwd = get_myenv("PWD", &*envs);
        printf("%s\n", pwd);
    }
}
