/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarella <pcarella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 22:36:16 by dzuntini          #+#    #+#             */
/*   Updated: 2022/02/04 22:40:39 by pcarella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define END 0
# define LEFT 1
# define LLEFT 2
# define RIGHT 3
# define RRIGHT 4
# define TXT 5
# define PIPE 6

# define RESET "\x1b[0m"
# define CYAN "\x1b[36m"

# include "../libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>
# include <signal.h>
# include <time.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <limits.h>
# include <sys/wait.h>

typedef struct s_token
{
	int		type;
	char	*str;
}			t_token;

typedef struct s_cmd
{
	int		pipefd[2];
	int		nb_redir;
	t_token	*redir_tab;
	int		ac;
	char	**av;
	char	**path;
	pid_t	pid;
	int		exit_code;
}			t_cmd;

typedef struct s_vars
{
	int			nb_cmd;
	t_cmd		*cmd;
	int			exit_status;
	int			in_cpy;
	int			out_cpy;
	char		*pwd;
	char		*home;
	int			tab_len;
	char		***tab_env;
	char		***tab_exp;
	char		**e;
	char		**word_tab;
	int			nb_tkn;
	t_token		*tk_tab;
}				t_data;

typedef struct s_process
{
	int		status;
	int		exit_code;
	pid_t	pid;
	int		interrupt_hd;
}		t_process;

t_process	g_sig;

void		welcometext(void);
void		expand(char **str, t_data *ms);
void		parser(t_data *ms);
int			tokenize(t_data *ms);
int			exec(t_data *ms);
void		sigint_handler(int code);
void		sigquit_handler(int code);
void		exit_error(char *str, int mode);
t_token		*ft_tokenize(char **tab);
char		**get_cmd_path(t_data *ms, char *cmd);
void		exec_cmds(t_data *ms);
void		test(int code);
void		test_slash(int code);
void		test2(int code);
void		ft_print(t_data *ms);
int			get_type(char *token);
void		expanser(char **tab, t_data *ms);
int			lexer(t_data *ms, char *line);
int			check_syntax(char **tab);
void		get_env(t_data *ms, char **env);
void		buitlin_init(t_data *ms, char **env);
int			builtin_env(t_data *ms, char **param);
int			builtin_echo(char **param);
int			builtin_export(t_data *ms, char **param);
char		**split_export(char *param);
int			sort_export(t_data *ms);
int			find_export(t_data *ms, char *param);
void		print_export(char **print);
int			error_export(char *param);
char		**min_export(t_data *ms, char **min);
int			builtin_unset(t_data *ms, char **param);
int			builtin_cd(t_data *ms, char **param);
int			builtin_exit(t_data *ms, char **param);
int			builtin_pwd(t_data *ms, char **param);
int			builtin(t_data *ms, int n);
void		echo_control_seq(int c);
int			redir(t_token *tk_tab);
char		*get_tabenv(t_data *ms, char *key);
void		init_data(t_data *ms, char **e);
char		*ft_readline(char *str);
void		ft_readline2(int fd, char *del);
void		clear(void);
int			builtin_check(char *check);
void		print_error(char *str, int mode);
int			is_sep(char c);
int			len_sep(char *str);
void		exit_error(char *str, int mode);
char		**ft_translate(t_data *ms);
void		exec_fork(t_data *ms, int cpt);
int			get_exit_code(t_data *ms);
void		exec_cmd(t_cmd c, char **e);
void		ft_replace_str(char **line, t_data *ms);
int			is_finished(char *str);
void		free_tkn(t_token *tkn_list);
void		ft_free(char **tab);

void		free_vars(t_data *ms);
void		free_matrix(char ***matrix);
void		free_cmd(t_cmd	*cmd_list, int n);
void		free_tabstr(char **tab);
void		free_tkns(t_token *tkn_list);

void		init_tabexp(t_data *ms);
int			ft_tabexp_len(char ***matrix);
char		**copy_env(char *key, char *val);
void		add_exp(t_data *ms, char *key, char *val);
int			print_exp(t_data *ms);

int			print_env(t_data *ms);
int			update_export(t_data *ms, char *param);

int			is_builtin(char *str);
void		exec_solo_built(t_data *ms);

void		fill_heredoc(t_data *ms, t_cmd c);
int			is_true_builtin(char *str);
char		**get_cmd_path(t_data *ms, char *cmd);

int			join_export(t_data *ms, char *param, int select);
t_cmd		fill_cmd(t_data *ms, int ic, int i);
char		**add_elem(char **av, char *str);
int			get_exit_code(t_data *ms);
void		atomic_exec(t_data *ms, int cpt);
void		exec_binary(t_cmd cmd, char **e);
#endif
