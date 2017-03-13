##
## Makefile for  in /home/sabbah_j/rendu/TEK2/B4-SystemeUnix/PSU_2014_zappy/zappy_gui/API_Client
## 
## Made by jordan sabbah
## Login   <sabbah_j@epitech.net>
## 
## Started on  Sun Jun 21 19:19:25 2015 jordan sabbah
## Last update Sun Jul  5 23:06:50 2015 jordan sabbah
##

CC		= g++

RM		= rm -rf

CXXFLAGS	= -Wall -Werror -Wextra -std=c++11 -fPIC
CXXFLAGS	+= -I../Error -I../API_Loader -I../API_Protocol -I.
CXXFLAGS	+= -I../API_Mutex -I../API_Mutex/Implementation/API_Mutex_SFML
CXXFLAGS	+= -I../API_Thread -I../API_Thread/Implementation/API_Thread_SFML
CXXFLAGS	+= -I../API_GUI -I../API_Protocol -I.. -I../API_Thread/Implementation/API_Thread_C
CXXFLAGS	+= -I../API_Mutex/Implementation/API_Mutex_C
CXXFLAGS	+= -I../API_Socket/Implementation/API_Socket_Unix
CXXFLAGS	+= -I../API_Socket

LDFLAGS		= -ldl -shared
LDFLAGS		+= -lsfml-graphics -lsfml-window -lsfml-system
LDFLAGS		+= -L../SOs -Wl,-rpath=../SOs
LDFLAGS		+= -l_API_Error -l_API_Thread_C -l_API_Mutex_C
LDFLAGS		+= -l_API_Socket_Unix -l_API_Protocol -l_API_GUI_SFML
LDFLAGS		+= -Wl,-rpath=../../zappy_gui/SOs
LDFLAGS		+= -Wl,-rpath=../../zappy_gui/API_Client


SRCS		= Window.cpp		\
		  Client.cpp		\
		  InfoClient.cpp

OBJS		= $(SRCS:.cpp=.o)

NAME		= ../SOs/lib_API_Client.so

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CXXFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)
clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

