##
## Makefile for  in /home/sabbah_j/rendu/TEK2/B4-SystemeUnix/PSU_2014_zappy/zappy_gui/API_Protocol
## 
## Made by jordan sabbah
## Login   <sabbah_j@epitech.net>
## 
## Started on  Thu Jun 18 23:53:23 2015 jordan sabbah
## Last update Sat Jul  4 17:12:55 2015 jordan sabbah
##

CC		= g++

RM		= rm -rf

CXXFLAGS	= -Wall -Werror -Wextra -std=c++11 -fPIC
CXXFLAGS	+= -I../API_Socket -I../Error -I../API_Loader
CXXFLAGS	+= -I../API_Socket/Implementation/API_Socket_Unix
CXXFLAGS	+= -I../API_Mutex -I../API_Socket/Implementation/API_Socket_Unix
CXXFLAGS	+= -I../API_GUI -I.

LDFLAGS		= -ldl -shared
LDFLAGS		+= -L../SOs -Wl,-rpath=../SOs
LDFLAGS		+= -l_API_Error -l_API_Mutex_C
LDFLAGS		+= -l_API_Socket_Unix
LDFLAGS		+= -Wl,-rpath=../../zappy_gui/SOs
LDFLAGS		+= -Wl,-rpath=../../zappy_gui/API_Protocol


SRCS		+= Protocol.cpp				\
		   ServerCommand.cpp

OBJS		= $(SRCS:.cpp=.o)

NAME		= ../SOs/lib_API_Protocol.so

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

