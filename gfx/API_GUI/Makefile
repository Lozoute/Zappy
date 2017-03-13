##
## Makefile for  in /home/sabbah_j/rendu/TEK2/B4-SystemeUnix/PSU_2014_zappy/API_GUI
## 
## Made by jordan sabbah
## Login   <sabbah_j@epitech.net>
## 
## Started on  Tue Jun  9 12:44:24 2015 jordan sabbah
## Last update Sun Jul  5 23:07:08 2015 jordan sabbah
##

CC		= g++

RM		= rm -rf

CXXFLAGS	= -Wall -Werror -Wextra -std=c++11 -fPIC
CXXFLAGS	+= -I../Error -I../API_Loader -I../API_Protocol -I.
CXXFLAGS	+= -I../API_Mutex -I../API_Mutex/Implementation/API_Mutex_SFML
CXXFLAGS	+= -I../API_Thread -I../API_Thread/Implementation/API_Thread_SFML
CXXFLAGS	+= -I../API_Client -I.. -I../API_Mutex/Implementation/API_Mutex_C
CXXFLAGS	+= -I../API_Mutex

LDFLAGS		= -ldl -shared
LDFLAGS		+= -lsfml-graphics -lsfml-window -lsfml-system
LDFLAGS		+= -L../SOs -Wl,-rpath=../SOs
LDFLAGS		+= -l_API_Error -l_API_Mutex_C -l_API_Protocol
LDFLAGS		+= -Wl,-rpath=../../zappy_gui/SOs
LDFLAGS		+= -Wl,-rpath=../../zappy_gui/API_GUI


SRCS		= Cell.cpp				\
		  Map.cpp				\
		  Object.cpp				\
		  Team.cpp				\
		  Player.cpp				\
		  SpritePlayer.cpp			\
		  GameEngine.cpp			\
		  Egg.cpp				\
		  Broadcast.cpp


OBJS		= $(SRCS:.cpp=.o)

NAME		= ../SOs/lib_API_GUI_SFML.so

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CXXFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)
clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

