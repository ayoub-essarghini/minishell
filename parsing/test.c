#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <string.h>

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

int    check_input(char *s)
{
    int check = strcmp(s, "exit");
    if(!check)
    {
        exit(0);
    }
    if(!all_space(s) || (strcmp(s, "")) == 0)
    {
        return (1);
    }
    return (0);
}

int main()
{
    char *line;
    while(1)
    {
        line = readline("MADNESS_SHELL->$ ");
        if(check_input(line))
        line = readline("MADNESS_SHELL->$ ");
        if(strlen(line) > 0)
        {
            printf("%s\n", line);
            add_history(line);
        }
    }
}