#ifndef PARSING_H
#define PARSING_H

#include "minishell.h"
#include <stdio.h>
#include "./parsing/libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <string.h>




typedef enum s_state
{
	Single = 1,
	Double = 2,
	General = 0
} state;

typedef enum e_token
{
	WORD,
	WHITE_SPACE,
	OPTION,
	NEW_LINE,
	QOUTE,
	DOUBLE_QUOTE,
	ESCAPE,
	ENV,
	PIPE_LINE,
	REDIR_IN,
	REDIR_OUT,
	HERE_DOC,
	DREDIR_OUT,
} t_token;

typedef struct s_list
{
	char *input;
	state status;
	t_token token;
	struct s_list *next;
	struct s_list *prev;
} t_list;

//  PARSING
int check_line(char *str);
void get_line(t_list **tab, char *line);
void check_nodes(t_list *tab);
void check_first(t_list *tab, t_envs *envs);

// execution
void set_envs(char *envs[], t_envs **envs_lst);
char *get_value(char *str);
char *get_key(char *str);
void exec_builtin(t_list *cmds, t_envs **envs);
void set_defautl_env(t_envs **envs);
void remove_env(t_list *cmds, t_envs **envs);
void set_export(t_list *cmds, t_envs **envs);
void get_export(char *key, char *value, t_envs **envs);
void print_env(t_envs **envs);
int exist_env(char *key, t_envs **envs);
void append_to_env(t_envs **envs, char *key, char *value);
char *get_myenv(char *key,t_envs **envs);
void change_directory(t_list *cmds, t_envs **envs);
void exec_non_buitin(t_list *tab, t_envs **envs);
int exec_with_pipeline(t_list *tab);


// linked list
t_list *ft_lstlast(t_list *lst);
int ft_lstsize(t_list *lst);
void ft_lstadd_back(t_list **lst, t_list *envs);
void creat_nodes(t_list **head, char *input, int status);
t_list *ft_lstnew(char *input, int status);
t_envs *ft_lstlast2(t_envs *lst);
int ft_lstsize2(t_envs *lst);
void ft_lstadd_back2(t_envs **lst, t_envs *envs);
t_envs *ft_lstnew2(char *key, char *value);
void creat_node(t_envs **head, char *key, char *value);
// utils
void print_nodes(t_list *tab);
void ft_free(t_list *tab);
void ft_error(t_list *tab);

#endif