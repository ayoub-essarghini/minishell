#include "parsing.h"


int    gnl(char **line)
{
    char    buffer[1000000];
    int        i;
    int        r;
    char    c;

    i = 0;
    r = read(0, &c, 1);
    while (r > 0 && c != '\n' && c != '\0')
    {
        buffer[i++] = c;
        r = read(0, &c, 1);
    }
    buffer[i] = '\0';
    *line = buffer;
    if (r > 0 || i > 0)
        return (1);
    else
        return (r);
}

void    herdoc(char *limiter, int *fd)
{
    char    *line;

    close(fd[0]);
    write(1, "heredoc> ", 9);
    while (gnl(&line) > 0)
    {
        if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
           exit(EXIT_SUCCESS);
        write(fd[1], line, ft_strlen(line));
        write(fd[1], "\n", 1);
        write(1, "heredoc> ", 9);
    }
    close(fd[1]);
    exit(EXIT_SUCCESS);
}

void    open_heredoc(char *delim)
{
    int    fd[2];
    pid_t    pid;

    if (pipe(fd) == -1)
        perror("here_doc Pipe");
    pid = fork();
    if (pid == -1)
        perror("here_doc fork");
    if (pid == 0)
    {
        herdoc(delim, fd);
    }
    else
    {
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);
        wait(NULL);
    }
}


//////////////////////////////////////////

// void open_heredoc(char *here_doc, char *delim)
// {
//     int fd[2];
//     //int in;
 
//     // if (fd == -1)
//     // {
//     //     perror("open");
//     //     return;
//     // }

//     char *str;
//     str = ft_strdup(" ");
//     while (1)
//     {
//         str = readline(">");

//         if (ft_strncmp(str, delim, ft_strlen(delim)) == 0)
//             break;

//         if (!str)
//             continue;
//         ft_putendl_fd(str, fd[1]);
//     }
//     if (str)
//         free(str);
//  //close(fd);

//     // Unlink the temporary file after use
//    // unlink("/tmp/.heredoc");
// }
// void set_heredoc(t_heredoc **heredoc, t_list *cmds)
// {

//     t_list *tmp = cmds;

//     while (tmp)
//     {
//         if (tmp->token == HERE_DOC && tmp->next != NULL)
//             creat_node3(&*heredoc, tmp->input, tmp->next->input);
//         tmp = tmp->next;
//     }
// }
// void handle_here_doc(t_list *tab, t_envs *envs)
// {

//     t_heredoc *heredoc = NULL;

//     set_heredoc(&heredoc, tab);
//     if (heredoc != NULL)
//     {
//         while (heredoc)
//         {
//             printf("%s->%s\n", heredoc->here_doc, heredoc->delimiter);
//             open_heredoc(heredoc->here_doc, heredoc->delimiter);
//             heredoc = heredoc->next;
//         }
//     }
//     else
//         perror("heredoc");
// }