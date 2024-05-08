#include "parsing.h"

void open_heredoc(char *here_doc, char *delim)
{
    int pipefd[2];
    pid_t pid, rdr;

    printf("were in\n");

    if (pipe(pipefd) == -1)
    {
        perror("pipe");
    }

    pid = fork();
    if (!pid)
    {                       /* COMMAND RUNNER PROCESS */
        dup2(pipefd[0], 0); /* set stdin to pipe's read end */
        close(pipefd[1]);   /* close pipe's write end */
                            /* exec command (will read from stdin) */
                            execvp("ls",NULL);
    }
    rdr = fork();
    if (!rdr)
    {                     /* INPUT READER PROCESS */
        close(pipefd[0]); /* close pipe's read end */

        /* read input from stdin until a line containing only
           the end of input marker is found */
        char buf[1024];
        while (fgets(buf, sizeof(buf), stdin))
        {
            /* break when end of input marker is read */
            if (!strcmp(buf, delim))
                break;
            /* write data to pipe */
            write(pipefd[1], buf, strlen(buf));
        }
        return ;
    }
    close(pipefd[0]); /* close pipe's read end */
    close(pipefd[1]);
}
void set_heredoc(t_heredoc *heredoc, t_list *cmds)
{

    t_list *tmp = cmds;

    while (tmp)
    {
        if (tmp->token == HERE_DOC && tmp->next != NULL)
            creat_node3(&heredoc, tmp->input, tmp->next->input);
        tmp = tmp->next;
    }

    // while (heredoc)
    // {
    //     printf("%s -> %s\n", heredoc->here_doc, heredoc->delimiter);
    //     heredoc = heredoc->next;
    // }
}
void handle_here_doc(t_list *tab, t_envs *envs)
{

    t_heredoc *heredoc = NULL;

    set_heredoc(heredoc, tab);
    while (heredoc)
    {
        printf("%s->%s\n",heredoc->here_doc,heredoc->delimiter);
        // open_heredoc(heredoc->here_doc, heredoc->delimiter);
        heredoc = heredoc->next;
    }
}