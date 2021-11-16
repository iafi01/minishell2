/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmedas <dmedas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 01:29:25 by dmedas            #+#    #+#             */
/*   Updated: 2021/11/12 18:14:59 by dmedas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define CLEAR "\033[H\033[J"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <errno.h>
# include <termios.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/ioctl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/includes/libft.h"

typedef enum e_bool{
	false,
	true
}			t_bool;

typedef enum e_type
{
	TK_ID,
	TK_PIPE,
	TK_EQ,
	TK_QUOTE,
	TK_SQUOTE,
	TK_GREATER,
	TK_LOWER,
	TK_DGREA,
	TK_DLOW,
	TK_BREAK,
	CM_ECHO,
	CM_CD,
	CM_PWD,
	CM_EXP,
	CM_UNS,
	CM_ENV,
	CM_EXIT,
	EXIT_STATUS,
	CM_CMD,
	CM_OPT
}	t_type;

typedef struct s_envp
{
	char			*first;
	char			*second;
	int				index;
	struct s_envp	*next;
}				t_envp;

typedef struct s_token
{
	t_type			e_type;
	struct s_token	*next;
	char			*val;
	int				apici;
	struct s_token	*prec;
}				t_token;

typedef struct s_redirect
{
	char	*file;
	t_type	red_type;
}			t_redirect;

typedef struct s_command
{
	char				*cmd;
	t_list				*out;
	t_list				*in;
	t_list				*here_doc;
	t_list				*par;
	struct s_command	*next;
}				t_command;

typedef struct s_global
{
	int				argc;
	int				ret;
	t_bool			set;
	t_token			*token;
	char			**argv;
	char			**args;
	char			**envp;
	struct s_envp	*env;
	t_command		*simple_cmd;
	int				size;
	int				pid;
	t_bool			last;
	t_bool			one;
}				t_global;

t_global	g_glbl;

//debug
void		ft_print_token(t_token *token);

//minishell.c
void		sign_handler(int sig);
void		ft_lexer(char *line, t_token *token);
int			ft_get_size(char **envp);
char		*ft_stringa_unica(char *line, int *j, int ap);
char		*str_2loop(char *line, int *j, char *tmp, char *s);
char		*ft_apici_split(char *line);
int			lex_last_if(char *line, int *i, t_token *token, char **tmp);

//parsing.c
int			init_parsing(char *line);
char		*skip_spaces(char *str);
int			check_apici(char *line);
int			cerca_apici(char *line);
int			control_apici(int s_apici, int d_apici);
int			ft_apici_invers(char *line);
int			ft_apici_0(char *line);
int			ft_apici_1(char *line);
int			ft_apici_2(char *line);
void		add_list_loop(char ***dollar, int *i, char *val, char **tmp);

//parsing2.c
int			command_by_path(char *line);
int			command(char *line);
int			parsing_comand(char *line);
int			solo_spazi(char *line);

//parsing3.c
char		*ft_alpha_give(char *s);
char		*ft_symbols_give(char *s);
int			ft_add_list(t_token *list, t_type type, char *val, int apici);
int			ft_token_priority(t_global *global, t_token *token);
int			ft_is_command(enum e_type i);
void		end_echo(int *flag, int fd, t_global *global);

//parser.c
int			ft_parsing(t_global *global);
int			ft_exec_build_in(t_global *global,
				t_command *cmd, int fdi, int fdo);
int			ft_print_envvar(char *line, t_global *global);
int			check_apice(char *line);

//command.c
int			ft_pwd(int fd);
int			ft_env(t_global *global, int fd);
int			ft_cd(t_token *token);
int			ft_echo(t_global *global, int fd);
int			ft_unset(t_global *global, char *find);
void		exit_if(char **arr, t_global *global, int i);

//debug.c
void		debug(int d_apici, int s_apici, int prev_apici);
void		debug_list(t_token *token);
void		print_tokens(t_global *global);
void		print_str(char *str);

//utils.c
char		*cerca_variabile(char *line);
int			count_var(char *line);
int			cerca_token(t_token *token, enum e_type type);
int			store_token(t_token *list, char *t);
t_token		*ft_find_end(t_token *list);

//utils2.c
char		**list_to_arr(t_token *token);
char		**lst_to_arr(t_list *list);
t_token		*arr_to_list(char **arg);
char		**arr_add_front(char **arr, char *str, int len);
t_envp		*ft_env_new(char *envp);
int			check_path(t_global *global, t_token *tkn, char *cmd);
char		*search_path(char **paths, char *cmd);
int			ft_listlen(t_token *token);
char		*find_path(char **envp, char *cmd);
char		*find_path2(char **paths, char *cmd);

//redirections.c
int			ft_redirect_maggiore(t_redirect *red, int *fdo);
int			ft_redirect_minore(char *file, int *fdi);
void		ft_redirect(t_command *coms, int *fdi, int *fdo);
char		*find_path2(char **paths, char *cmd);
void		free_arr(char **arr);
int			first_apice(char *line);

//signals.c
void		sig_handler(int signum);
void		rl_replace_line(const char *text, int clear_undo);

//utils3.c
void		write_b(int n);
int			ft_get_size(char **envp);
char		**ft_copy_env(char **envp);
t_type		check_tokens_valid(t_token *token);
void		stringa_unica_aux(char *line, int *j, char **tmp);

//command2.c
t_envp		*ft_env_new(char *envp);
void		create_export(char **envp, t_envp *test);
void		set_index_export(t_global *global, t_envp *env);
int			sostitute_set(t_global *global, int export);

//command1.c
void		ft_set(t_global *global, char *find);
int			ft_export(t_global *global, int fdo);
void		ft_exit(t_global *global);

//parsing4.c
t_token		*init_token(int type, char *val);
int			is_token(char *c);
int			is_token_type(int i);
t_token		*ft_token_new(t_type token, char *val, int apici, t_token *prec);
void		ft_free_list(t_token *list);

//utils4.c
char		**get_options(t_token *token);
t_token		*find_cmd(t_token *token);
int			check_if_options(t_token *tkn, char *opt);
int			check_if_cmd(t_token *tkn);
int			is_path(char *str);
int			ft_free(void *ptr);
void		ft_free_lst(t_list *lst);
void		ft_free_cmd(t_command *cmd);
char		*str_2if(char *line, int *j, char *tmp);

// utils5.c
void		ft_print_error(char *str);
size_t		get_size_simple_com(t_command *coms);
char		*str_tolower(char *str);
t_redirect	*ft_new_redirect(char *file, t_type red_type);
void		*ft_free_redirect(t_redirect *to_free);

//utils6.c
void		dollar_expand(char *line, char **tmp, int *j, int ap);
char		*expand_env_var(char *str, int *i, char *result);
void		str_unica_complement(char *s, char *line, char **tmp, int *j);
void		str_append(char *line, int *j, char **tmp, char *s);
char		*ft_get_env_var(char *var, char **env);

//utils7.c
t_bool		all_n(char *str);
void		free_envp(t_envp *env);
void		ft_set_fds(pid_t pid, int *fds, int fdi, int fdo);
t_bool		ft_str_unic_aux(int *j, char *line, int *ap);
int			ft_lex_inception(char **tmp, char *line, t_token *token, int *i);

//state.c
t_command	*ft_state_0(t_token *token, t_command *cmd);
t_command	*ft_state_10(t_token *token, t_command *cmd);
t_command	*ft_state_1(t_token *token, t_command *cmd, t_type red_type);
t_command	*ft_state_2(t_token *token, t_command *cmd);
t_command	*ft_state_3(t_token *token, t_command *cmd);

//state2.c
t_command	*ft_state_4(t_token *token, t_command *cmd);
t_command	*ft_state_11(t_token *token, t_command *cmd, t_type red_type);
t_command	*ft_state_12(t_token *token, t_command *cmd);
t_command	*ft_state_13(t_token *token, t_command *cmd);

//state3.c
t_command	*ft_command_new(void);
t_command	*ft_cmd_init(t_command *cmd);

//executor.c
void		ft_exe_commands(t_global *global, t_command *simple_coms);
int			ft_redirect_pipe(t_global *global, t_command *cmd);
int			ft_exe_one(t_global *global, t_command *coms);

#endif
