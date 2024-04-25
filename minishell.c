#include "parsing.h"

int main()
{
    char *line;
    t_list *tab;
    
    tab = NULL;
    while(1)
    {
        line = readline("MADNESS_SHELL->$ ");
        if(ft_strlen(line) > 0 && !check_line(line))
        {
            get_line(&tab, line);
            check_nodes(tab);
            print_nodes(tab);
            check_first(tab);
            add_history(line);
            ft_free(tab);
            tab = NULL;
        }
        free(line);
    }
}