# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dfiliagg <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/20 10:46:16 by dfiliagg          #+#    #+#              #
#    Updated: 2023/05/30 10:27:42 by adi-fort         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell
FLAGS	=  -Wall -Wextra -Werror
CC		= gcc ${FLAGS}
RM		= rm -f
SRC		= minishell.c  free.c exit_status.c ${BLT} ${PIP} ${ARG} ${PRS} ${SIG}
BLT     = builtin/envp_utils.c builtin/pwd_utils.c builtin/exit_utils.c builtin/our_echo.c builtin/our_cd.c builtin/our_cd2.c builtin/export_utils.c builtin/export_utils2.c builtin/export_utils3.c builtin/export_utils4.c builtin/unset_utils.c 
PRS		= parse/parse.c parse/parse2.c parse/matrix.c parse/parse_utils.c parse/check.c parse/matrix2.c
ARG     = args/args_utils.c args/args.c args/sost_arg.c args/args_utils2.c
PIP		= pipex/pipex_utils.c pipex/pipex.c pipex/pipex2.c pipex/error.c pipex/check_file.c pipex/command_list.c pipex/exe_builtin.c pipex/in_redirect.c pipex/ambient.c
SIG		= signal/signal.c
OBJ		= ${SRC:.c=.o}
LFT		= libft/libft.a

all: ${NAME}

${LFT}:
		make -C libft
.o:.c
	${CC} ${OBJ} -c $< -o ${<:.c=.o}

${NAME}: ${OBJ} ${LFT}
	${CC} ${OBJ} ${LFT} -o ${NAME} -lreadline

clean:
	${RM} ${OBJ}
	make clean -C libft

fclean: clean
	${RM} ${NAME}
	make fclean -C libft

re: fclean all

.PHONY: all clean fclean re