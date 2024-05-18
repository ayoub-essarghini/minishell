#include "parsing.h"

char *conv_to_cmds(t_list *tab)
{
    char *str = NULL;
    int total_length = 0;
    t_list *temp = tab;

    // First pass: calculate the total length needed for the resulting string
    while (temp)
    {
        // Check if the current token is not a redirection token and if the previous token is not a redirection token
        if (temp->token != REDIR_IN && temp->token != REDIR_APPEND && temp->token != REDIR_OUT && temp->token != HERE_DOC &&
            (!temp->prev || (temp->prev->token != REDIR_IN && temp->prev->token != REDIR_APPEND && temp->prev->token != REDIR_OUT && temp->prev->token != HERE_DOC)))
        {
            total_length += strlen(temp->input) + 1; // +1 for the space or null terminator
        }
        temp = temp->next;
    }

    // Allocate memory for the resulting string
    str = (char *)malloc(total_length + 1);
    if (!str)
        return NULL;

    str[0] = '\0'; // Initialize the string with null terminator
    temp = tab;

    // Second pass: concatenate the valid command parts into the resulting string
    while (temp)
    {
        // Check if the current token is not a redirection token and if the previous token is not a redirection token
        if (temp->token != REDIR_IN && temp->token != REDIR_APPEND && temp->token != REDIR_OUT && temp->token != HERE_DOC &&
            (!temp->prev || (temp->prev->token != REDIR_IN && temp->prev->token != REDIR_APPEND && temp->prev->token != REDIR_OUT && temp->prev->token != HERE_DOC)))
        {
            strcat(str, temp->input);
            strcat(str, " ");
        }
        temp = temp->next;
    }

    // Remove the trailing space
    if (total_length > 0)
    {
        str[total_length - 1] = '\0';
    }

    return str;
}


int check_pipes(int (*pipefds)[2], int n)
{

    int j = 0;
    while (j < n - 1)
    {
        if (pipe(pipefds[j]) == -1)
        {
            perror("pipe");
            return (-1);
        }
        j++;
    }
    return 0;
}

int exec_with_pipeline(t_list *tab, t_envs **envs)
{
    char *str = conv_to_cmds(tab);
    char **arr = ft_split(str, '|');
    int i = 0;

    while (arr[i])
    {
        // printf("[%s]\n",arr[i]);
        i++;
    }

    int(*pipefds)[2] = malloc(sizeof(int[2]) * (i - 1));

    if (!pipefds)
        printf("error ocurred");

    if (check_pipes(pipefds, i) == -1)
        exit(EXIT_FAILURE);

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

            // Redirect output to next command  input
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

            char *args[32] = {0}; // Assuming maximum 31 arguments
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
            if (is_builtin(args[0]) == 0)
            {
                exec_builtin(tab, &*envs);
                // perror(args[0]);
                exit(EXIT_SUCCESS);
                // rl_redisplay();
            }
            else
            {

                int ii = 0;
                while (paths && paths[ii])
                {
                    // printf("----->%p\n",envs);
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
        }
        k++;
    }

    // Close remaining pipes in the parent process
    int j = 0;
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
    free(pipefds);

    return (0);
}
