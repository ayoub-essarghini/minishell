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
    else if (ft_strcmp(cmds->input, "cd") == 0)
    {
        // printf("cd");
        if (cmds->next != NULL)
        {
            char *root = get_myenv("HOME",&*envs);
            if (cmds->input[0] == '/')
                printf("is it");
            // root = ft_strjoin(root, cmds->next->input);
            // printf("%s\n", root);
            // if (chdir("/nfs") == -1)
            // {
            //     perror("cd");
            // }

            // pid_t pid = fork();

            // if (pid == 0)
            // {
            // char *s[] = {"ls", "-la", NULL};
            // if (execve("/bin/ls", s, NULL) == -1)
            // {
            //     perror("ls");
            // }

            // }
            // else
            // {
            //     wait(NULL);
            // }
      
        }
    }
}
