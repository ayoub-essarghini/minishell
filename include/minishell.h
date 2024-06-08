/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sarg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 19:54:24 by aes-sarg          #+#    #+#             */
/*   Updated: 2024/06/08 22:20:59 by aes-sarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MINISHELL_H
# define MINISHELL_H

# include "./parsing.h"

typedef struct s_pipeline_info
{
	int	num_cmds;
	int	cmd_index;
}		t_pipeinfo;

int		handle_redirections(t_token type, char *filename, int *fd);
int		exec_with_pipeline(t_cmd *tab, t_envs **envs);
char	*get_value(char *str);
char	*get_key(char *str);
void	print_env(t_envs **envs, int flag);
void	get_export(char *key, char *value, int flag, t_envs **envs);
void	set_export(char **cmds, t_envs **envs);
void	remove_env(char **cmds, t_envs **envs);
int		exist_env(char *key, t_envs **envs);
void	echo_cmd(char **cmds, t_envs *envs);
void	exec_non_builtin(char **args, t_red *rd, t_envs **envs);
void	ft_exit(char **cmds, t_cmd *tabcmd, t_envs *envs, int flag);
void	exec_builtin(t_cmd *tabcmd, char **cmds, t_red *red, t_envs **envs);
void	with_relative_path(char **cmds, t_envs **envs);
void	with_absolute_path(char **cmds, t_envs **envs);
void	change_directory(char **cmds, t_envs **envs);
void	handle_builtin_exit(t_cmd *cmd, t_envs **envs, int (*svinout)[2]);
void	handle_builtin(t_cmd *cmd, t_envs **envs, int (*svinout)[2]);
void	handle_external_cmd(t_cmd *cmd, t_envs **envs, int (*svinout)[2]);
int		is_builtin(char *cmd);
void	exec_cmd(t_cmd **tabcmd, t_envs **envs);
int		apply_redirections(t_red *rd, int *sv_in, int *sv_out);
void	restore_redirections(int saved_stdin, int saved_stdout);
int		red_in(char *filename, int *fd);
int		red_out(char *filename, int *fd);
int		red_app(char *filename, int *fd);
int		ft_lst_size(t_cmd *cmds);
void	close_pipes_in_parent(int (*pipefds)[2], int count);
void	wait_for_children(int num_cmds, pid_t *pids);
void	change_to_root(t_envs **envs);
void	change_to_prev(char **cmds, t_envs **envs);
void	change_to_old(char **cmds, t_envs **envs);
char	*ft_strncpy(char *dest, const char *src, int n);
void	export_error(char *cmd, char *message);
void	set_or_append_env(t_envs **envs, char *key, char *value, int flag);
int		is_valid_key(char *key);
void	ft_error(char *cmd, char *message);
int		exec_with_path(char **args, t_envs *envs);
void	exec_not_bin(char **args, t_envs **envs, int sv_in, int sv_out);
char	*get_cmd_bin(char **args, t_envs **envs);
void	check_other_exec(char **args, t_envs **envs, int sv_in, int sv_out);
void	command_404(char *cmd);
int		exec_simple(char *full_cmd, char **args, t_envs *envs);
void	free_and_exit(char *full_cmd, char **args, int sv_in, int sv_out);
int		parent_proc(int *pid);
void	create_pipes(int (*pipefds)[2], int count);
void	free_env_node(t_envs *node);
void	swap(t_envs *a, t_envs *b);
void	remove_env_key(char *key_to_remove, t_envs **envs);
void	sort_env_list(t_envs *head);
t_envs	*dup_envs(t_envs *envs);
int		check_key_val(char *key, char *value, int flag, t_envs **envs);
int		is_append_or_add(char *str);
void	check_exec_res(int result, char *full_cmd, char **args,
			int (*svinout)[2]);
void	close_and_wait(int num_cmds, pid_t *pids, int (*pipefds)[2]);
int		is_contain_n(char *str);
void	pipe_err(void);
void	init_pipes(int (**pipefds)[2], int num_cmds);
void	handle_exit_too_many_args(int flag);
void	handle_exit_numeric(char **cmds, t_cmd *tabcmd, t_envs *envs);
void	handle_exit_non_numeric(char **cmds, t_cmd *tabcmd, t_envs *envs);
pid_t	*init_pids(int num_cmds);
void	set_or_append_pwd(t_envs **envs, char *key, char *value, int flag);
void	update_env_value(t_envs *env, char *key, char *new_value);
void	print_env_list(t_envs *current);
void	export_the_key_and_values(char *cmd, t_envs **envs, int flag);
void	print_export(t_envs *current);
void	change_dir_cleanup(char *cwd, char *pwd, char *oldpwd);
void	set_or_append_pwd(t_envs **envs, char *key, char *value, int flag);
void	handle_single_arg(char **cmds, t_envs **envs);
void	check_val(char *value, char **new_value, char *tmp_value);
#endif
