#include "parsing.h"

int handle_redirections(t_list *node, int *saved_stdin, int *saved_stdout)
{
    int fd;
    int here_doc_fd[2];
    char *here_doc_delim = NULL;

    while (node)
    {
        if (node->token == REDIR_IN)
        {
            fd = open(node->next->input, O_RDONLY);
            if (fd < 0)
            {
                perror("open input file");
                return -1;
            }
            *saved_stdin = dup(STDIN_FILENO);
            if (dup2(fd, STDIN_FILENO) < 0)
            {
                perror("dup2 input");
                return -1;
            }
            close(fd);
        }
        else if (node->token == REDIR_OUT)
        {
            fd = open(node->next->input, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd < 0)
            {
                perror("open output file");
                return -1;
            }
            *saved_stdout = dup(STDOUT_FILENO);
            if (dup2(fd, STDOUT_FILENO) < 0)
            {
                perror("dup2 output");
                return -1;
            }
            close(fd);
        }
        else if (node->token == REDIR_APPEND)
        {
            fd = open(node->next->input, O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (fd < 0)
            {
                perror("open append file");
                return -1;
            }
            *saved_stdout = dup(STDOUT_FILENO);
            if (dup2(fd, STDOUT_FILENO) < 0)
            {
                perror("dup2 append");
                return -1;
            }
            close(fd);
        }
        else if (node->token == HERE_DOC)
        {
            if (pipe(here_doc_fd) == -1)
            {
                perror("pipe");
                return -1;
            }
            here_doc_delim = node->next->input;
            char *line;
            printf("heredoc> ");
            while ((line = readline("")) != NULL)
            {
                if (strcmp(line, here_doc_delim) == 0)
                {
                    free(line);
                    break;
                }
                write(here_doc_fd[1], line, strlen(line));
                write(here_doc_fd[1], "\n", 1);
                free(line);
                printf("heredoc> ");
            }
            close(here_doc_fd[1]);
            *saved_stdin = dup(STDIN_FILENO);
            if (dup2(here_doc_fd[0], STDIN_FILENO) < 0)
            {
                perror("dup2 heredoc");
                return -1;
            }
            close(here_doc_fd[0]);
        }
        node = node->next;
    }
    return 0;
}

// Function to restore original file descriptors
void restore_redirections(int saved_stdin, int saved_stdout)
{
    if (saved_stdin >= 0)
    {
        dup2(saved_stdin, STDIN_FILENO);
        close(saved_stdin);
    }
    if (saved_stdout >= 0)
    {
        dup2(saved_stdout, STDOUT_FILENO);
        close(saved_stdout);
    }
}

t_list *remove_red(t_list *curr)
{
    t_list *new = NULL;  // Initialize the new list to NULL
    // t_list *last = NULL; // To keep track of the last element in the new list
    t_list *tmp = curr;
    while (tmp)
    {
        if (tmp->token != REDIR_APPEND && tmp->token != REDIR_IN &&
            tmp->token != REDIR_OUT && tmp->token != HERE_DOC &&
            (tmp->prev && (tmp->prev->token != REDIR_APPEND && tmp->prev->token != REDIR_IN &&
                           tmp->prev->token != REDIR_OUT && tmp->prev->token != HERE_DOC)))
        {
            // creat_nodes(&new,tmp->input,tmp->status);
            // if (!last)
            // {
                printf("added \n");
            creat_last(&new, tmp->input, tmp->token, tmp->status);
                // last->next = new;
            // }
            // last = new;
        }
        tmp = tmp->next; // Move to the next element
    }
    // }

    return new;
}

// Function to execute a command with redirections
void execute_command_with_redirection(t_list *tab, t_envs **envs)
{
    int saved_stdin = -1, saved_stdout = -1;

    // Handle redirections and save original stdin and stdout
    if (handle_redirections(tab, &saved_stdin, &saved_stdout) == -1)
    {
        perror("redirect");
    }

    // Remove redirection nodes from the list and get a new list without redirections
    // t_list *tmp = remove_red(tab);
    // // // Use the new list if any redirection nodes were removed, otherwise use the original list
    // t_list *cmd_list;
    // cmd_list = (tmp != NULL) ? tmp : tab;

    // // Print the new list (for debugging purposes)
    // printf("here before\n");
    // print_nodes(cmd_list);
    // printf("here\n");

    // Check if there are any pipes in the command list
    if (exist_pipe(tab) == -1)
    {
        // If no pipe exists, check if it's a built-in command and execute it
        if (is_builtin(tab->input) == 0)
        {
            exec_builtin(tab, envs);
        }
        else
        {
            exec_non_builtin(tab, envs);
        }
        // printf("pipe not exist\n");
    }
    else
    {

        // printf("pipe exist\n");
        // If there are pipes, handle pipeline execution
        exec_with_pipeline(tab, envs);
    }

    // // Restore original stdin and stdout
    restore_redirections(saved_stdin, saved_stdout);
}
