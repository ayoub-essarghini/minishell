#include "parsing.h"

void open_heredoc(char *here_doc, char *delim)
{
    int fd;
    pid_t pid;

    pid = fork();

    if (pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0)
    {
        fd = open("/tmp/.herdoc", O_CREAT | O_TRUNC | O_RDWR, 0666);
     
       
        char *str;
        str = ft_strdup(" ");
        while (1)
        {
            str = readline(">");

            if (ft_strncmp(str, delim, ft_strlen(delim)) == 0)
                break;

            if (!str)
                continue;
            ft_putendl_fd(str, fd);
        }
        if (str)
            free(str);
        close(fd);
        // unlink("/tmp/.herdoc");
    }
    else
    {
        wait(NULL);
    }
}
