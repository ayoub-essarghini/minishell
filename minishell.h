#ifndef MINISHELL_H
#define MINISHELL_H

#define COLOR_RED "\033[31m"
#define COLOR_GREEN "\033[1;34m"
#define COLOR_RESET "\033[0m"

typedef struct s_envs
{
    char *key;
    char *value;
    struct s_envs *next;
} t_envs;




#endif