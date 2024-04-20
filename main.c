#include "minishell.h"

char *ft_strjoin(char const *s1, char const *s2)

{
    char *new_str;
    int i;
    int j;

    if (!s1 && !s2)
        return (0);
    if (!s1)
        return (strdup(s2));
    if (!s2)
        return (strdup(s1));
    new_str = (char *)malloc(strlen(s1) + strlen(s2) + 1);
    if (!new_str)
        return (NULL);
    i = 0;
    while (s1[i] != '\0')
    {
        new_str[i] = s1[i];
        i++;
    }
    j = 0;
    while (s2[j] != '\0')
        new_str[i++] = s2[j++];
    new_str[i] = '\0';
    return (new_str);
}

int excute_cmd(char *cmd[])
{
    printf("%s\n", cmd[1]);
    if (strcmp(cmd[0], "ls") == 0)
    {
        if (execvp(cmd[0], cmd) == -1)
        {
            printf("execution failed ");
            return (-1);
        }
    }
    return (0);
}
int main()
{
    t_infos *infos = (t_infos *)malloc(sizeof(t_infos));

    while (1)
    {
        char cwd[1045];
        if (getcwd(cwd, sizeof(cwd)) == NULL)
        {
            perror("getcwd");
            exit(EXIT_FAILURE);
        }

        char *name = strrchr(cwd, '/');
        name = ft_strjoin(" \033[33m", name + 1);
        name = ft_strjoin(name, "\33[0m\033[33m ➜\033[0m ");
        char *input = readline(name);

        if (!input)
        {
            printf("\n");
            break;
        }

        char *cmd = strtok(input, " ");
        int i = 0;
        while (cmd != NULL)
        {
            infos->cmd[i] = (char *)malloc(sizeof(char) * (strlen(cmd) + 1));
            strcpy(infos->cmd[i], cmd);
            cmd = strtok(NULL, " ");
            i++;
        }
        infos->cmd[i] = NULL;

        if (strcmp(input, "exit") == 0)
        {
            printf("exit..\n");
            break;
        }

        pid_t pid = fork();

        if (pid == -1)
        {
            perror("fork error");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0)
        {
            excute_cmd(infos->cmd);
        }
        else
        {
            wait(NULL);
        }
    }
}