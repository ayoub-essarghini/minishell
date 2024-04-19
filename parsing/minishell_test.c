#include "parsing.h"


int main()
{
    ft_putstr_fd("$ ", 1);
    int fd = 0;
    char *line;
    t_list *list;
    while(line = get_next_line(fd))
    {
        store_map(line, &list);
        ft_putstr_fd("$ ", 1);
    }
}