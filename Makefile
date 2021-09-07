NAME = minishell

HEADER = includes/
LIBFT = libft/
FLAGS = -Wall -Wextra
LFLAGS = -L libft -lft

FOLDER = srcs

SRCS_LIST = minishell.c parsing.c parsing2.c parsing3.c command.c debug.c \
			parser.c utils.c

SRCS = $(addprefix ${FOLDER}/, ${SRCS_LIST})

all: $(LIB) $(NAME)

$(NAME):
	@make -s -C $(LIBFT)
	@gcc -o $(NAME) $(FLAGS) $(SRCS) $(LFLAGS) -I $(HEADER)
	@echo "\033[1m$(NAME)\033[0m""\033[32m	Compiled\033[0m"
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