##
## Makefile for  in /home/sabbah_j/rendu/TEK2/B4-SystemeUnix/PSU_2014_zappy/zappy_gui/API_Protocol
## 
## Made by jordan sabbah
## Login   <sabbah_j@epitech.net>
## 
## Started on  Thu Jun 18 23:53:23 2015 jordan sabbah
## Last update Sat Jul  4 03:12:14 2015 jordan sabbah
##

CC		= g++

RM		= rm -rf

CXXFLAGS	= -Wall -Werror -Wextra -std=c++11
CXXFLAGS	+= -I../Error -I../API_Loader
CXXFLAGS	+= -I../API_GUI -I../API_Protocol/ -I../API_Mutex/Implementation/API_Mutex_SFML
CXXFLAGS	+= -I../API_Mutex -IImplementation/API_Thread_C
CXXFLAGS	+= -I. -I..
LDFLAGS		= -ldl -lsfml-graphics -lsfml-window -lsfml-system -L../SFML -Wl,-rpath=../SFML

SRCS		+= ../Error/Error.cpp			\
		   ../API_Loader/Loader.cpp		\
		   ../API_Loader/OpenLib_Unix.cpp	\
		   ../API_Mutex/ScopedLock.cpp		\
		   ../API_GUI/GameEngine.cpp		\
		   ../API_Protocol/ServerCommand.cpp	\
		   ../API_GUI/Map.cpp			\
		   ../API_GUI/Player.cpp		\
		   ../API_GUI/Cell.cpp			\
		   ../API_GUI/Object.cpp		\
		   ../API_GUI/Window.cpp		\
		   ../API_GUI/Team.cpp			\
		   ../API_GUI/SpritePlayer.cpp		\
		   main.cpp

OBJS		= $(SRCS:.cpp=.o)

NAME		= a.out

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

