NAME = minishell

HEADER = includes/
LIBFT = libft/
FLAGS = -Wall -Wextra
LFLAGS = -L libft -lft

RFLAGS = -lreadline -I ./homebrew/Cellar/readline/8.1.1/include -L ./homebrew/Cellar/readline/8.1.1/lib
FOLDER = srcs

SRCS_LIST = minishell.c minishell2.c lex_utils.c parsing.c parsing2.c parsing3.c command.c debug.c signals.c\
			parser.c utils.c utils2.c redirections.c utils3.c utils5.c utils4.c state.c state2.c \
			state3.c command1.c command2.c parsing4.c expander.c executor.c pipe.c\

HOMEBREW = homebrew/opt/readline/lib

SRCS = $(addprefix ${FOLDER}/, ${SRCS_LIST})

all: $(HOMEBREW) $(LIB) $(NAME)

$(NAME):
	@make -s -C $(LIBFT)
	@gcc -o $(NAME) $(FLAGS) $(SRCS) $(LFLAGS) $(RFLAGS) -I $(HEADER) -lreadline -g
	@echo "\033[1m$(NAME)\033[0m""\033[32m	Compiled\033[0m"

$(HOMEBREW):
	mkdir homebrew && curl -L https://github.com/Homebrew/brew/tarball/master | tar xz --strip 1 -C homebrew
	./homebrew/bin/brew install readline
	
clean:
	@make clean -C $(LIBFT) 
	@/bin/rm -f *.o
	@echo "Objects ""\033[34m	Cleaned\033[0m"

fclean: clean
	@make fclean -C $(LIBFT)
	@/bin/rm -f $(NAME)
	@echo "Project ""\033[31m	Cleaned\033[0m"

re: fclean all

git:
	git add .
	git commit -m "ft_tree"
	git push
