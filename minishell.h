#ifndef MINISHELL_H
#define MINISHELL_H
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>
#include <readline/readline.h>

#define COLOR_RED     "\033[31m"
#define COLOR_GREEN   "\033[1;34m"
#define COLOR_RESET   "\033[0m"


typedef struct s_infos{

    char *cwd;
    char *cmd[];

    

}   t_infos;





















#endif