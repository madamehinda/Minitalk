# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hferjani <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/20 14:48:07 by hferjani          #+#    #+#              #
#    Updated: 2022/10/12 15:27:46 by hferjani         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# artifacts
CLIENT = client
SERVER = server

# compiler
CC = gcc -g3

# flags
CFLAGS = -Wall -Werror -Wextra
DEBUG_FLAGS = -g

# source files
SERVER_SRCS := server.c \
	utils.c 
CLIENT_SRCS := client.c \
	utils.c

# object files
SERVER_OBJS := ${SERVER_SRCS:.c=.o}
CLIENT_OBJS := ${CLIENT_SRCS:.c=.o}

HEADER = minitalk.h

# rules
all: ${CLIENT} ${SERVER}

${CLIENT}: ${CLIENT_OBJS}
	${CC} ${CFLAGS} ${CLIENT_OBJS} ${LIBFTPRINTF} ${LIBCLIENT} -o $@

${SERVER}: ${SERVER_OBJS}
	${CC} ${CFLAGS} ${SERVER_OBJS} ${LIBFTPRINTF} ${LIBSERVER} -o $@

%.o: %.c
	${CC} ${CFLAGS} ${DEBUG_FLAGS} -o $(<:.c=.o) -c $<

clean:
	${RM} ${SERVER_OBJS} ${CLIENT_OBJS}

fclean: clean
	${RM} ${CLIENT} ${SERVER} 

re: fclean all

.PHONY: all clean fclean re norme
