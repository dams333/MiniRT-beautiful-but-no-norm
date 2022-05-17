# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/06 09:16:50 by dhubleur          #+#    #+#              #
#    Updated: 2022/05/17 12:42:27 by dhubleur         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	$(addprefix srcs/, \
				main.c \
				$(addprefix parser/, \
					parser.c \
					parse_util.c \
					parser_c_a_l.c))
				
OBJS	=	${SRCS:.c=.o}
INCL	=	-I./includes -I./libft

NAME	=	miniRT
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror

RM		=	rm -f

LIBFT	=	libft/libft.a

.c.o:
				${CC} ${CFLAGS} ${INCL} -c $< -o ${<:.c=.o}

all:		${NAME}
bonus:		${NAME}

$(NAME):	${OBJS} ${LIBFT} ${LIBMLX}
				${CC} -o ${NAME} ${OBJS} ${LIBFT} -lm

$(LIBFT):
				$(MAKE) -C libft all

clean:
				${RM} ${OBJS}

fclean:		clean
				${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re bonus