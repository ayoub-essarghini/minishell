#include "parsing.h"
void set_and_colorize_prompt(char cwd[1045], char **name, char *root)
{

    *name = strrchr(cwd, '/');

    root = getenv("HOME");
    root = strrchr(root, '/');

    if (strcmp(*name + 1, root + 1) == 0)
    {

        *name = ft_strjoin("", "\033[33m ➜\033[0m ");
    }
    else
    {
        *name = ft_strjoin(" \033[33m", *name + 1);
        *name = ft_strjoin(*name, "\33[0m\033[33m ➜\033[0m ");
    }
}
int main()
{
    char cwd[1045];
    char *name = NULL;
    t_list *tab;
    char *root = NULL;
    char *cmd = NULL;

    tab = NULL;
    while (1)
    {

        if (getcwd(cwd, sizeof(cwd)) == NULL)
        {
            perror("getcwd");
            exit(EXIT_FAILURE);
        }
        set_and_colorize_prompt(cwd, &name, root);
        cmd = readline(name);
        if (ft_strlen(cmd) > 0 && !check_line(cmd))
        {
            get_line(&tab, cmd);
            check_nodes(tab);
            print_nodes(tab);
            // check_first(tab);
            add_history(cmd);
            ft_free(tab);
            tab = NULL;
        }
        // free(cmd);
    }
}