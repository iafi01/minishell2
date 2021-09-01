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

typedef struct s_global
{
    int  argc;
    char **line;
    char **argv;
    char **envp;
    char **args;
}   t_global;

//minishell.c


//parsing.c
int     init_parsing(char *line);
char    *skip_spaces(char *str);
int     check_apici(char *line);
int     cerca_apici(char *line);
int     print_err_apici(int s_apici, int d_apici);


//parsing2.c
int     command_by_path(char *line);
int	    command(char *line);
int	    parsing_comand(char *line);
int	    solo_spazi(char *line);

//parsing3.c
int	    check_corr_pos_apici(char *line);

//command.c
int ft_tree(t_global *global);
#endif