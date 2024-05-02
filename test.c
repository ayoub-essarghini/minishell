#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <readline/readline.h>

#define MAX_COMMANDS 16

int main() {
    char *input;

    while (1) {
        // Read user input
        printf("minishell$ ");
        fflush(stdout); // Flush stdout to ensure prompt is displayed
        input = readline(" ");

        // Parse user input into commands
        char *commands[MAX_COMMANDS];
        int num_commands = 0;

        char *token = strtok(input, "|");
        while (token != NULL && num_commands < MAX_COMMANDS) {
            commands[num_commands++] = token;
            token = strtok(NULL, "|");
        }

        // Create pipes
        int pipefds[num_commands - 1][2];
        for (int i = 0; i < num_commands - 1; i++) {
            if (pipe(pipefds[i]) == -1) {
                perror("pipe");
                exit(EXIT_FAILURE);
            }
        }

        // Fork and execute commands
        pid_t pid;
        int prev_pipefd = STDIN_FILENO;
        for (int i = 0; i < num_commands; i++) {
            if ((pid = fork()) == -1) {
                perror("fork");
                exit(EXIT_FAILURE);
            } else if (pid == 0) {
                // Child process
                // Redirect input from previous command's output
                if (i > 0) {
                    dup2(pipefds[i - 1][0], STDIN_FILENO);
                    close(pipefds[i - 1][0]); // Close read end of previous pipe
                    close(pipefds[i - 1][1]); // Close write end of previous pipe
                }

                // Redirect output to next command's input
                if (i < num_commands - 1) {
                    dup2(pipefds[i][1], STDOUT_FILENO);
                    close(pipefds[i][0]); // Close read end of current pipe
                    close(pipefds[i][1]); // Close write end of current pipe
                }

                // Close all other pipes
                for (int j = 0; j < num_commands - 1; j++) {
                    if (j != i - 1) {
                        close(pipefds[j][0]);
                        close(pipefds[j][1]);
                    }
                }

                // Parse command and arguments
                char *args[32]; // Assuming maximum 31 arguments
                int num_args = 0;

                char *arg_token = strtok(commands[i], " \n");
                while (arg_token != NULL) {
                    args[num_args++] = arg_token;
                    arg_token = strtok(NULL, " \n");
                }
                args[num_args] = NULL;

                // Execute command
                execvp(args[0], args);
                perror("execvp");
                exit(EXIT_FAILURE);
            } else {
                // Parent process
                // Close read end of previous pipe
                if (i > 0) {
                    close(pipefds[i - 1][0]);
                    close(pipefds[i - 1][1]);
                }
            }
        }

        // Close remaining pipe
        if (num_commands > 1) {
            close(pipefds[num_commands - 2][0]);
            close(pipefds[num_commands - 2][1]);
        }

        // Wait for all child processes to finish
        for (int i = 0; i < num_commands; i++) {
            wait(NULL);
        }

        // Free memory allocated for input
        free(input);
    }

    return 0;
}
