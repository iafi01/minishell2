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

int	exit_status;

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
	char *first;
	char *second;
	int index;
	struct s_envp *next;
} t_envp;

typedef struct s_token
{
	t_type	e_type;
    struct  s_token *next;
	char	*val;
	int		apici; //0, 1, 2
	struct s_token *prec;
}	t_token;

typedef struct	s_command
{
	char	*cmd;
	char	*out;
	char	*in;
	t_token	*par;
}				t_command;

typedef struct s_global
{
    int  	argc;
    t_token	*token;
    char 	**argv;
    char 	**args;
	char	**envp;
	struct s_envp *env;
	int		size;
}   			t_global;

//minishell.c
void    sign_handler(int sig);
void	ft_parse_split(char *line, t_token *token);
int		ft_get_size(char **envp);

//parsing.c
int     init_parsing(char *line);
char    *skip_spaces(char *str);
int     check_apici(char *line);
int     cerca_apici(char *line);
int     control_apici(int s_apici, int d_apici);


//parsing2.c
int     command_by_path(char *line);
int	    command(char *line);
int	    parsing_comand(char *line);
int	    solo_spazi(char *line);

//parsing3.c
char *ft_alpha_give(char *s);
char *ft_symbols_give(char *s);
int	ft_add_list(t_token *list, t_type type, char *val, int apici);
int ft_token_priority(t_global *global, t_token *token);


//parser.c
int ft_parsing(t_global *global);
int exec_build_in(t_global *global, t_token *token, int fd);
int ft_print_envvar(char *line, t_global *global);
int	check_apice(char *line);

//command.c
int	ft_pwd(int fd);
int	ft_env(t_global *global, int fd);
int	ft_cd(t_token *token);
int		ft_echo(t_global *global, int fd);
int    ft_unset(t_global *global);

//debug.c
void 	debug(int d_apici, int s_apici, int prev_apici);
void	debug_list(t_token *token);
void	print_tokens(t_global *global);

//utils.c
char	*cerca_variabile(char *line);
int	count_var(char* line);
int cerca_token(t_token *token, enum e_type type);
int	store_token(t_token *list, char *t);
t_token	*ft_find_end(t_token *list);

//utils2.c
char 	**list_to_arr(t_token *token);
t_token *arr_to_list(char **arg);
t_envp	*ft_env_new(char *envp);
int		check_path(t_global *global, t_token *tkn, char *cmd);
char	*search_path(char **paths, char *cmd);

char	*find_path(char **envp, char *cmd);
char	*find_path2(char **paths, char *cmd);

//redirections.c
int ft_redirect_maggiore(t_global *global, t_token *token);
int ft_redirect_pipe(t_global *global, t_token *token);
int ft_redirect_minore(t_global *global, t_token *token);
int ft_redirect_dmaggiore(t_global *global, t_token *token);
int ft_redirect_dminore(t_global *global, t_token *token);

void	free_arr(char **arr);
int first_apice(char *line);
//signals.c

void	sig_handler(int signum);

//utils3.c
void	write_b(int n);
int	ft_get_size(char **envp);
char **ft_copy_env(char **envp);

//command2.c
t_envp	*ft_env_new(char *envp);
void create_export(char **envp, t_envp *test);
void	set_index_export(t_global *global, t_envp *env);
int sostitute_set(t_global *global, int export);

//command1.c
void ft_set(t_global *global);
int	ft_export(t_global *global, int fd);
int ft_exit(t_global *global);

//parsing4.c
t_token	*init_token(int type, char *val);
int	is_token(char *c);
int	is_token_type(int i);
t_token	*ft_token_new(t_type token, char *val, int apici, t_token *prec);
void	ft_free_list(t_token *list);

//utils4.c
char	**get_options(t_token *token);
t_token *find_cmd(t_token *token);
int		check_if_options(t_global *global, t_token *tkn, char *opt);
int	check_if_cmd(t_token *tkn);
int		is_path(char *str);


#endif