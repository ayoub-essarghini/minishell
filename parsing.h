#ifndef PARSING_H
#define PARSING_H

#include "minishell.h"
#include <stdio.h>
#include "./parsing/libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

/// AST ---> ABSTRACT SYNTAX TREE

typedef struct s_tree t_ast;
typedef struct PIPE_CHILDS t_pipe;

typedef enum s_type
{
    CMD,
    PIPE
}t_type;

typedef struct s_cmd
{
	char **command;
	int fd;
}t_cmd;

typedef struct s_kind
{
	t_pipe *child;
	t_cmd *command;

}t_kind;

struct PIPE_CHILDS
{
    t_ast *left;
    t_ast *right;
};

struct s_tree
{
    t_type type;
    t_kind *syn;
};

typedef enum s_state
{
	Single = 1,
	Double = 2,
	General = 0
} state;

typedef enum e_token
{
	WORD = 0,
	WHITE_SPACE = 1,
	OPTION = 2 ,
	NEW_LINE = 3 ,
	QOUTE = 4 ,
	DOUBLE_QUOTE = 5,
	ESCAPE = 6,
	ENV = 7,
	PIPE_LINE = 8,
	REDIR_IN = 9,
	REDIR_OUT = 10,
	HERE_DOC = 11,
	APPEND = 12 ,
	QUOTES_SPACES = 13,
	NOT_DEF = 14,
	CONCATED = 15,
	REDIR_APPEND = 16,
} t_token;

typedef struct s_list
{
	char *input;
	state status;
	t_token token;
	struct s_list *next;
	struct s_list *prev;
} t_list;

typedef struct s_fds
{
	int saved_stdin;
	int saved_stdout;
} t_fds;

typedef struct s_redirect
{
	char *input;
	char *file;
	t_token token;
	struct s_redirect *next;

} t_red;

//  PARSING
void    ft_parse_line(char *line, t_list **tab, t_list **last, t_envs **envs);
void    ft_split_line(t_list **tab, char *line);
void	ft_check_concate(t_list **tab, t_list **last);
void	check_node(t_list *tab, t_envs *envs);
void    check_parsing(t_list **last, t_ast *root);

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
int is_builtin(char *cmd);
int exist_env(char *key, t_envs **envs);
void append_to_env(t_envs **envs, char *key, char *value);
char *get_myenv(char *key,t_envs **envs);
void echo_cmd(t_list *cmds, t_envs *envs);
void change_directory(t_list *cmds, t_envs **envs);
void exec_non_builtin(t_list *tab, t_envs **envs);
void exec_non_builtin(t_list *tab, t_envs **envs);
int exec_with_pipeline(t_list *tab, t_envs **envs);
void handle_here_doc(t_list *tab, t_envs *envs);
void open_heredoc(char *here_doc, char *delim);
int exist_pipe(t_list *tab);
void execute_command_with_redirection(t_list *tab, t_envs **envs);

// linked list
t_list *ft_lstlast(t_list *lst);
int ft_lstsize(t_list *lst);
void ft_lstadd_back(t_list **lst, t_list *envs);
void ft_lstadd_front(t_list **lst, t_list *new);
void creat_nodes(t_list **head, char *input, int status);
t_list *ft_lstnew(char *input, int status);
t_envs *ft_lstlast2(t_envs *lst);
int ft_lstsize2(t_envs *lst);
void ft_lstadd_back2(t_envs **lst, t_envs *envs);
t_envs *ft_lstnew2(char *key, char *value);
void creat_node(t_envs **head, char *key, char *value);
void ft_lstadd_between(t_list *prev, t_list *next, t_list *new);
void	creat_last(t_list **head, char *input, t_token token, state status);
t_list	*ft_lstnewlast(char *input, t_token token, state status);
void ft_lstdelete(t_list *node, t_list *next, t_list *prev, t_list *curr_next);

// utils
int    check_line(char *str);
int    all_space(char *str);
void    ft_free(t_list *tab);
int 	all_alpha(char *str);
void    print_nodes(t_list *tab);



//here doc list
void creat_redirection(t_red **h, char *input, t_token token, char *file);
t_red *ft_lstnew3(char *input, t_token token, char *file);
void ft_lstadd_back3(t_red **lst, t_red *new);
int ft_lstsize3(t_red *lst);
t_red *ft_lstlast3(t_red *lst);

#endif