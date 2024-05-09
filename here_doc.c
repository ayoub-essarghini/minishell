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
void set_heredoc(t_heredoc **heredoc, t_list *cmds)
{

    t_list *tmp = cmds;

    while (tmp)
    {
        if (tmp->token == HERE_DOC && tmp->next != NULL)
            creat_node3(&*heredoc, tmp->input, tmp->next->input);
        tmp = tmp->next;
    }
}
void handle_here_doc(t_list *tab, t_envs *envs)
{

    t_heredoc *heredoc = NULL;

    set_heredoc(&heredoc, tab);
    if (heredoc != NULL)
    {
        while (heredoc)
        {
            printf("%s->%s\n", heredoc->here_doc, heredoc->delimiter);
            open_heredoc(heredoc->here_doc, heredoc->delimiter);
            heredoc = heredoc->next;
        }
    }
    else
        perror("heredoc");
}