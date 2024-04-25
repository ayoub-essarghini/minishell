#include "../parsing.h"

int    all_space(char *str)
{
    int i;

    i = 0;
    while(str[i] == ' ' || str[i] == '\t')
    i++;
    if(str[i] == '\0')
        return (0);
    return (1);
}

int    check_line(char *str)
{
    int check = ft_strcmp(str, "exit");
    if(!check)
    {
        exit(0);
    }
    if(!all_space(str) || (ft_strcmp(str, "")) == 0)
    {
        return (1);
    }
    return (0);
}

