#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>

int main()
{
    char *input;
    while (1)
    {
        input = readline("\033[31mminishell$ \033[0m");

        if (!input)
        {
            printf("\n");
            break;
        }
        if (strcmp(input, "exit") == 0)
        {
            // printf("Exiting the program...\n");
            // free(input);
            break;
        }
         pid_t pid = fork();

        if (pid == -1) {
            perror("fork");
        } else if (pid == 0) {

            if (strcmp(input,"ls\n"))
            {
                char *args[] = {"ls","-la",NULL};
                if (execvp("ls",args)== -1)
                {
                    free(input);
                    exit(EXIT_FAILURE);
                }
            }else if (strcmp(input,"cd Desktop\n"))
            {
                char *args[] = {"cd","Desktop",NULL};
                if (chdir("~/Desktop")== -1)
                {
                    free(input);
                    exit(EXIT_FAILURE);
                }
            }
          
            // printf("Child process executing: %s\n", input);
      
            free(input); 
            exit(EXIT_SUCCESS);
        } else {
         
            wait(NULL);
            free(input);
        }
    }
}