# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dcastagn <dcastagn@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/05 11:05:08 by dcastagn          #+#    #+#              #
#    Updated: 2023/05/09 10:32:19 by dcastagn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SRC = main.c
OBJ = ${SRC:.c=.o}
CC = gcc
FLAGS = -Wall -Wextra -Werror -lreadline
RM = rm -f

.o:.c
	${CC} ${FLAGS} -c $< -o ${<:.c=.o}

all: ${NAME}

${NAME}: ${OBJ}
	${CC} ${FLAGS} ${SRC} -o ${NAME}

clean:
	${RM} ${OBJ}

fclean: clean
	${RM} ${NAME}

re: fclean all
