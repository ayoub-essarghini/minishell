#include "parsing.h"

char *conv_to_cmds(t_list *tab)
{
    char *str = NULL;
    int total_length = 0;
    t_list *temp = tab;

    while (temp)
    {
        total_length += strlen(temp->input) + 1;
        temp = temp->next;
    }
    str = (char *)malloc(total_length + 1);
    if (!str)
        return NULL;

    str[0] = '\0';
    temp = tab;
    while (temp)
    {
        strcat(str, temp->input);
        strcat(str, " ");
        temp = temp->next;
    }

    return str;
}


int exec_with_pipeline(t_list *tab)
{
    char *str = conv_to_cmds(tab);
    char **arr = ft_split(str, '|');

    int i = 0;
    while (arr[i])
        printf("%s\n", arr[i++]);

    int pipefds[i - 1][2];
    int c = 0;
    while (c < i - 1)
    {
        if (pipe(pipefds[c]) == -1)
            perror("pipe");
        c++;
    }

    pid_t pid;
    c = 0;
    int prev_pipefd = STDIN_FILENO;
    while (c < i)
    {
        if ((pid = fork()) == -1)
        {
            perror("fork");
        }
        else if (pid == 0)
        {
            if (c > 0)
            {
                dup2(pipefds[c - 1][0], STDIN_FILENO);
                close(pipefds[c - 1][0]);
                close(pipefds[c - 1][1]);
            }
            if (c < i - 1)
            {
                dup2(pipefds[c][1], STDOUT_FILENO);
                close(pipefds[c][0]);
                close(pipefds[c][1]);
            }
            int k = 0;
            while (k < i - 1)
            {
                if (k != c)
                {
                    close(pipefds[k][0]);
                    close(pipefds[k][1]);
                }
                k++;
            }
            
            execve("/bin/ls",)
            perror("execvp"); // Add error handling
            exit(EXIT_FAILURE);
        }
        else
        {
            if (c > 0)
            {
                close(pipefds[c - 1][0]);
                close(pipefds[c - 1][1]);
            }
        }
        c++;
    }

    int l = 0;
    while (l < i)
    {
        wait(NULL);
        l++;
    }

    return (0);
}
