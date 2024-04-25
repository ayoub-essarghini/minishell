#ifndef MINISHELL_H
#define MINISHELL_H

#define COLOR_RED "\033[31m"
#define COLOR_GREEN "\033[1;34m"
#define COLOR_RESET "\033[0m"

typedef struct s_envs
{
    char *key;
    char operator;
    struct s_envs *next;
} t_envs;

typedef struct s_infos
{

    char *cwd;
    char *cmd[];

} t_infos;

#endif