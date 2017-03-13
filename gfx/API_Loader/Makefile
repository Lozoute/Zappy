##
## Makefile for  in /home/sabbah_j/rendu/TEK2/B4-SystemeUnix/PSU_2014_zappy/API_Mutex/Implemantation/API_Mutex_STD
## 
## Made by jordan sabbah
## Login   <sabbah_j@epitech.net>
## 
## Started on  Sun Jun  7 16:31:19 2015 jordan sabbah
## Last update Sun Jun 21 14:09:52 2015 jordan sabbah
##

CC		= g++

RM		= rm -rf

CXXFLAGS	= -Wall -Wextra -Werror -std=c++11
CXXFLAGS	+= -I../API_Mutex -I../API_Mutex/Implementation/API_Mutex_C -I../Error

LDFLAGS		= -ldl

NAME		= a.out

SRC		= ../Error/Error.cpp		\
		  main.cpp			\
		  OpenLib_Unix.cpp		\
		  Loader.cpp			\
		  ../API_Mutex/ScopedLock.cpp

OBJS		= $(SRC:.cpp=.o)


all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(CXXFLAGS) $(LDFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
