# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kebab <kebab@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/14 16:19:42 by lmizzoni          #+#    #+#              #
#    Updated: 2021/08/31 12:22:23 by kebab            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libft.a

SRCS_LIST	= ft_isascii.c ft_isprint.c ft_isalpha.c ft_isdigit.c ft_isalnum.c \
			ft_tolower.c ft_toupper.c ft_strlen.c ft_strlcpy.c ft_strlcat.c \
			ft_strchr.c ft_strrchr.c ft_strnstr.c ft_strncmp.c ft_atoi.c \
			ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c \
			ft_memchr.c ft_memcmp.c ft_strdup.c ft_calloc.c ft_itoa.c \
			ft_putchar.c ft_putstr.c ft_putnbr.c \
			ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
			ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_strmapi.c \
			ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c \
			ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c \
			ft_set_split.c ft_str_delete.c ft_is_in_str.c ft_strlen_c.c \
			ft_atof.c ft_intlen.c ft_is_space.c ft_strcpy.c ft_strcat.c \
			ft_str_sim.c ft_str_end.c ft_char_count.c ft_isnum.c ft_atol.c \
			ft_strsplit.c get_next_line.c ft_strcmp.c \

SRCS		= $(addprefix ${FOLDER}/, ${SRCS_LIST})
OBJS		= ${SRCS:.c=.o}

HEADER		= includes
FOLDER		= srcs

CC			= gcc
CFLAGS 		= -Wall -Wextra -Werror #-fsanitize=address
RM			= rm -f

$(NAME):	${OBJS}
			@ar -rcs ${NAME} ${OBJS}

%.o: %.c
			@${CC} -c ${CFLAGS} -o $@ $< -I ${HEADER} -g

all:		${NAME}

clean:
			@${RM} ${OBJS}

fclean:		clean
			@${RM} ${NAME}

re:			fclean all

.PHONY: 	all fclean clean re