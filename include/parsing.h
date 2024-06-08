/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sarg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 18:20:15 by aes-sarg          #+#    #+#             */
/*   Updated: 2024/06/04 18:24:17 by aes-sarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PARSING_H
# define PARSING_H

# include "../libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/wait.h>

extern int				g_exit_status;

typedef enum e_token
{
	WORD = 0,
	WHITE_SPACE = 1,
	OPTION = 2,
	NEW_LINE = 3,
	QOUTE = 4,
	DOUBLE_QUOTE = 5,
	ESCAPE = 6,
	ENV = 7,
	PIPE_LINE = 8,
	REDIR_IN = 9,
	REDIR_OUT = 10,
	HERE_DOC = 11,
	APPEND = 12,
	QUOTES_SPACES = 13,
	NOT_DEF = 14,
	CONCATED = 15,
	REDIR_APPEND = 16,
	SPLIT_ENV,
	TO_CONC,
}						t_token;

// redirections ####################

typedef struct s_red
{
	char				*input;
	t_token				type;
	int					fd;
	int					saved_stdin;
	int					saved_stdout;
	struct s_red		*next;
	struct s_red		*prev;
}						t_red;

void					red_list_add(t_red **head, t_token type, char *input);
t_red					*dublicate_red_list(t_red *red);

// ##############################

typedef enum s_type
{
	cmd,
	pipe_line,
	last_cmd_pipe,
	redirection
}						t_type;

typedef struct s_command
{
	char				**tab;
	t_type				type;
	t_red				*red;
	int					fd;
	struct s_command	*next;
	struct s_command	*prev;
}						t_cmd;

typedef enum s_state
{
	Single = 1,
	Double = 2,
	General = 0
}						t_state;

typedef struct s_list
{
	char				*input;
	t_state				status;
	t_token				token;
	struct s_list		*next;
	struct s_list		*prev;
}						t_list;

typedef struct s_envs
{
	char				*key;
	char				*value;
	struct s_envs		*next;
}						t_envs;

t_envs					*ft_lstlast2(t_envs *lst);
int						ft_lstsize2(t_envs *lst);
void					ft_lstadd_back2(t_envs **lst, t_envs *new);
t_envs					*ft_lstnew2(char *key, char *value);
void					creat_node(t_envs **head, char *key, char *value);

char					*get_myenv(char *key, t_envs **envs);
void					set_envs(char *envs[], t_envs **envs_lst);
void					set_envs_list(int ac, char **av, char **envs,
							t_envs **env_list);
char					**convert_envs_to_arr(t_envs *envs);
void					set_defautl_env(t_envs **envs);
char					*get_value(char *str);
char					*get_key(char *str);
t_list					*check_env(t_list *tab, t_envs **envs);

// #################################################

//  PARSING #######################################################

void					ft_split_words(t_list **tab, char *str, int status);
int						ft_parse_line(char *line, t_cmd **tabcmd,
							t_envs **envs);
void					ft_split_line(t_list **tab, char *line);
void					ft_check_concate(t_list **tab, t_list **last);
void					parse_command_tab(t_list **list, t_cmd **tabcmd,
							t_envs **envs);
t_list					*ft_parse_redirections(t_list **list, t_red **red,
							t_envs **envs);
void					check_node(t_list **last, t_envs **envs);
int						parse_here_doc(t_list *list, t_envs **envs);
void					ft_token(t_list *tab);
void					expand_env_doc(t_list *new, t_envs **envs);

// linked list #####################################################

int						ft_lstsize(t_list *lst);
void					ft_lstadd_back(t_list **lst, t_list *envs);
void					ft_lstadd_front(t_list **lst, t_list *new);
void					creat_nodes(t_list **head, char *input, int status);
t_list					*ft_lstlast(t_list *lst);
t_list					*ft_lstnew(char *input, int status);
t_list					*ft_lstdelete(t_list *next_node, t_list *prev_node);
char					**convert_list_to_arr(t_list *lst);
int						count_args(t_list *list);

// for last list ###################################################

void					creat_last(t_list **head, char *input, t_token token,
							t_state status);
t_list					*ft_lstnewlast(char *input, t_token token,
							t_state status);

// for tab command ###################################################

void					creat_command(t_cmd **head, t_type type, char **arr,
							t_red **red);

// utils ##############################################################

int						check_redirections(t_token type);
int						check_quotes(char *line);
int						check_syntax(t_list *tab, t_envs **envs);
int						check_line(char *str);
int						all_space(char *str);
int						all_alpha(char *str);
int						ambiguous_redirect(t_list *last);
void					ft_free(t_list *tab);
void					print_nodes(t_list *tab);
void					ft_print_double_list(t_cmd *head);
void					ft_free_tab_command(t_cmd *tab);
void					ft_free_red(t_red *tab);
char					*ft_word(const char *str, int start, int end);
void					print_red(t_red *tab);
void					ft_free_env(t_envs *tab);
void					ft_history(t_list *tab, char *line);
void					print_error_msg(int flag, char *input);
void					ft_exit_free(t_cmd *tabcmd, t_envs *envs);
int						count_heredoc(t_list *last);
void					check_count_heredoc(int count);
char					*creat_name_heredoc(void);

// ################

int						white_spaces(t_list **tab, char *line, int start,
							int i);
int						single_quote(t_list **tab, char *line, int start,
							int i);
int						double_quote(t_list **tab, char *line, int start,
							int i);
int						envirm(t_list **tab, char *line, int start, int i);
int						pipe_linee(t_list **tab, char *line, int start, int i);
int						redir_in(t_list **tab, char *line, int start, int i);
int						redir_out(t_list **tab, char *line, int start, int i);
int						simple_word(t_list **tab, char *line, int start, int i);
void					word(t_list **tab, char *line, int start, int i);

// #######################################################################

void					print_ascii(void);

///////////////////=Signals=/////////////////

void					handle_doc_int(int signal);
void					herdoc_signal(void);
void					handle_child_int(int signal);
void					child_signal(void);
void					handle_sigint(int sig);
void					handle_sigquit(int sig);

#endif
