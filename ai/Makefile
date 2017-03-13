##
## Makefile for zappy_ia in /home/helleg_f/rendu/PSU_2014_zappy/ai
## 
## Made by florian hellegouarch
## Login   <helleg_f@epitech.net>
## 
## Started on  Tue Jun 16 15:40:29 2015 florian hellegouarch
## Last update Sun Jul  5 03:17:04 2015 florian hellegouarch
##

NAME		= ../zappy_ai

SRCS		= Client.cpp				\
		  Protocol.cpp				\
		  Player.cpp				\
		  ProtocolParser.cpp			\
		  Random.cpp				\
		  Fork.cpp				\
		  Level.cpp				\
		  Inventory.cpp				\
		  View.cpp				\
		  Broadcast.cpp				\
		  IaClientException.cpp			\
		  ConnectionException.cpp		\
		  main.cpp

FOLDER_SOCK	= c_socket

SRCS_SOCK	= $(FOLDER_SOCK)/socket_init.c		\
		  $(FOLDER_SOCK)/socket_close.c		\
		  $(FOLDER_SOCK)/perror_color.c		\
		  $(FOLDER_SOCK)/get_char.c		\
		  $(FOLDER_SOCK)/write_line.c

COBJS		= $(SRCS_SOCK:.c=.o)

OBJS		= $(SRCS:.cpp=.o)

CPP		= g++

RM		= rm -f

CFLAGS		+= -Wall -Wextra -Werror

CXXFLAGS	+= -Wall -Wextra -Werror
CXXFLAGS	+= -I./include
CXXFLAGS	+= -std=c++11

LDFLAGS		+= -pthread


all:		$(NAME)

$(NAME):	$(COBJS) $(OBJS)
		$(CPP) -o $(NAME) $(COBJS) $(OBJS) $(LDFLAGS)

clean:
		$(RM) $(OBJS) $(COBJS)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

.PHONY:		all clean fclean re
