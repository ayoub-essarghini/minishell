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
        i++;

    int pipefds[i - 1][2];
    int j = 0;
    while (j < i - 1)
    {
        if (pipe(pipefds[j]) == -1)
        {
            perror("pipe");
            exit(EXIT_FAILURE);
        }
        j++;
    }

    // Fork and execute commands
    pid_t pid;
    int k = 0;
    while (k < i)
    {
        if ((pid = fork()) == -1)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0)
        {
            // Child process
            // Redirect input from previous command's output
            if (k > 0)
            {
                dup2(pipefds[k - 1][0], STDIN_FILENO);
                close(pipefds[k - 1][0]); // Close read end of previous pipe
                close(pipefds[k - 1][1]); // Close write end of previous pipe
            }

            // Redirect output to next command's input
            if (k < i - 1)
            {
                dup2(pipefds[k][1], STDOUT_FILENO);
                close(pipefds[k][0]); // Close read end of current pipe
                close(pipefds[k][1]); // Close write end of current pipe
            }

            // Close all other pipes
            int l = 0;
            while (l < i - 1)
            {
                if (l != k && l != k - 1)
                {
                    close(pipefds[l][0]);
                    close(pipefds[l][1]);
                }
                l++;
            }

            char *args[32]; // Assuming maximum 31 arguments
            int num_args = 0;

            char *arg_token = strtok(arr[k], " \n");
            while (arg_token != NULL)
            {
                args[num_args++] = arg_token;
                arg_token = strtok(NULL, " \n");
            }
            args[num_args] = NULL;
            char *get_path = getenv("PATH");
            char **paths = ft_split(get_path, ':');
            int ii;
            while (paths[ii])
            {
                char *new_cmd = ft_strjoin(paths[ii], "/");
                new_cmd = ft_strjoin(new_cmd, args[0]);
                // printf("%s\n",new_cmd);
                if (execve(new_cmd, args, NULL) == -1)
                {
                    ii++;
                }
                else
                {
                    free(new_cmd);
                   
                }
                free(new_cmd);
            }
            perror(args[0]);
            exit(EXIT_FAILURE);
        }
        k++;
    }

    // Close remaining pipes in the parent process
    j = 0;
    while (j < i - 1)
    {
        close(pipefds[j][0]);
        close(pipefds[j][1]);
        j++;
    }

    // Wait for all child processes to finish
    int m = 0;
    while (m < i)
    {
        wait(NULL);
        m++;
    }

    return (0);
}
