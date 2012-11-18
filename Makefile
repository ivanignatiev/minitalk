##
## Makefile for minitalk in /home/ignati_i//test_c/minitalk
## 
## Made by ivan ignatiev
## Login   <ignati_i@epitech.net>
## 
## Started on  Mon Nov 12 14:17:54 2012 ivan ignatiev
## Last update Sun Nov 18 20:34:30 2012 ivan ignatiev
##

CLIENT_SRC	=	client_src/main.c

SERVER_SRC	=	server_src/main.c \
			server_src/clients.c \
			server_src/signals.c

STRINGMY_SRC	=	stringmy/my_putchar.c \
			stringmy/my_putstr.c \
			stringmy/my_puterror.c \
			stringmy/my_getnbr.c \
			stringmy/my_put_nbr.c

SERVER_NAME	=	server
CLIENT_NAME	=	client

CFLAGS		+=	-Werror -Wall -Wextra
CFLAGS		+=	-pedantic
CFLAGS		+=	-I./include/

SERVER_LDFLAGS	=
CLINET_LDFLAGS	=

CLIENT_OBJS	=	$(CLIENT_SRC:.c=.o)
SERVER_OBJS	=	$(SERVER_SRC:.c=.o)
STRINGMY_OBJS	=	$(STRINGMY_SRC:.c=.o)

CC		=	cc

RM		=	rm -f

all:			$(SERVER_NAME) $(CLIENT_NAME)
$(SERVER_NAME):		$(SERVER_OBJS) $(STRINGMY_OBJS)
			$(CC) -o $(SERVER_NAME) $(SERVER_OBJS) $(STRINGMY_OBJS) $(SERVER_LDFLAGS)
$(CLIENT_NAME):		$(CLIENT_OBJS) $(STRINGMY_OBJS)
			$(CC) -o $(CLIENT_NAME) $(CLIENT_OBJS) $(STRINGMY_OBJS) $(CLIENT_LDFLAGS)
clean:
			$(RM) $(SERVER_OBJS) $(CLIENT_OBJS) $(STRINGMY_OBJS)
fclean:			clean
			$(RM) $(SERVER_NAME) $(CLIENT_NAME)
re:			fclean all
.PHONY:			all clean fclean re
