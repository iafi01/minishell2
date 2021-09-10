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
	CM_EXIT
}	t_type;

typedef struct s_envp
{
	char *first;
	char *second;
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
t_token	*ft_token_new(t_type token, char *val, int apici, t_token *prec);
int		is_token(char *c);
void	ft_free_list(t_token *list);
int		ft_add_list(t_token *list, t_type type, char *val, int apici);
int	is_token_type(int i);

//parsing3.c
int	    check_apici_pos(char *line);

//parser.c
int ft_parsing(t_global *global);
int exec_build_in(t_global *global);
int ft_print_envvar(char *line, t_global *global);
int	check_apice(char *line);

//command.c
int ft_tree(t_global *global);
void	ft_pwd(void);
void	ft_env(t_global *global);
void	ft_cd(t_token *token);
int		ft_echo(t_global *global);

//debug.c
void 	debug(int d_apici, int s_apici, int prev_apici);
void	debug_list(t_token *token);

//utils.c
char	*cerca_variabile(char *line);
int	count_var(char* line);
int cerca_token(t_token *token, enum e_type type);
int	store_token(t_token *list, char *t);
t_token	*ft_find_end(t_token *list);

//utils2.c
char **list_to_arr(t_token *token);
t_token *arr_to_list(char **arg);

#endif