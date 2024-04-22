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

void execute_at_root()
{
    char *root = getenv("HOME");
    if (chdir(root) == -1)
    {
        perror("root file missed !");
        exit(EXIT_FAILURE);
    }
}
int excute_cmd(char *cmd)
{

    if (strcmp(cmd, "ls") == 0)
    {
        // cmd[1] = NULL;
        char *args[] = {cmd, NULL};
        if (execve("/bin/ls", args, NULL) == -1)
        {
            printf("execution failed ");
            return (-1);
        }
    }
    else if (strcmp(cmd, "ls -la") == 0)
    {
        // cmd[1] = NULL;
        char *args[] = {cmd, "-la", NULL};
        if (execve("/bin/ls", args, NULL) == -1)
        {
            printf("execution failed ");
            return (-1);
        }
    }
    else if (strncmp(cmd, "echo", 4) == 0)
    {
        if (strlen(cmd) > 4)
        {

            if (*(cmd + 4) == ' ' && *(cmd + 5) == '-' && *(cmd + 6) == 'n' && *(cmd + 7) != '\0')
            {
                // printf("done");
                char *c = cmd + 8;
                printf("%s", c);
            }  else
            {
            char *c = cmd + 5;
            printf("%s\n", c);
            }
        }
        else
        {
            printf("\n");
        }
      
    }
    else if (strncmp(cmd,"cd",2) == 0)
    {
        if (*(cmd+2) == '\0')
        {
            const char *home = getenv("HOME");
            if (chdir(home) == -1)
            {
                printf("No such file or directory !");
            }
            // char cwd[1045];

            // if (getcwd(cwd,sizeof(cwd)) != NULL)
            // {
            //     printf("%s\n",cwd);
            // }
        }
        else
        {
            if (chdir(cmd+3) == -1)
            {
                printf("No such file or directory !");
            }
            //  char cwd[1045];
            // if (getcwd(cwd,sizeof(cwd)) != NULL)
            // {
            //     printf("%s\n",cwd);
            // }
        }
    }
    else if (strncmp(cmd,"export",6) == 0)
    {
        const char *token = "test";
        const char *value = "22";
     if (setenv(token, value, 1) != 0) {
    perror("setenv error");
} else {
    printf("Environment variable %s set to %s\n", token, value);
}
    }

    return (0);
}

void handle_signal(int sig)
{
    if (sig == SIGINT)
    {
        printf("^C");
        rl_clear_signals();
       
    }
}
int main()
{

    execute_at_root();

    while (1)
    {

        // signal(SIGINT,handle_signal);
        char cwd[1045];
        if (getcwd(cwd, sizeof(cwd)) == NULL)
        {
            perror("getcwd");
            exit(EXIT_FAILURE);
        }

        char *name = strrchr(cwd, '/');                    

        char *root = getenv("HOME");
        root = strrchr(root,'/');
      
         if (strcmp(name+1,root+1) == 0)
        {
       
            name =ft_strjoin("","\033[33m ➜\033[0m ");
        }
        else
        {
        name = ft_strjoin(" \033[33m", name + 1);
        name = ft_strjoin(name, "\33[0m\033[33m ➜\033[0m ");
        }
        char *input = readline(name);

        if (!input)
        {
            printf("\n");
            break;
        }

        if (strcmp(input, "exit") == 0)
        {
            printf("exit\n");
            exit(EXIT_SUCCESS);
        }

        pid_t pid = fork();

        if (pid == -1)
        {
            perror("fork error");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0)
        {
            excute_cmd(input);
        }
        else
        {
            wait(NULL);
        }
    }
    return (0);
}