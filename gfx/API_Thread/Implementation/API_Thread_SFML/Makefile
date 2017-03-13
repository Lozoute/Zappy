##
## Makefile for  in /home/sabbah_j/rendu/TEK2/B4-SystemeUnix/PSU_2014_zappy/API_Thread/Implementation/API_Thread_SFML
## 
## Made by jordan sabbah
## Login   <sabbah_j@epitech.net>
## 
## Started on  Wed Jun 10 10:14:42 2015 jordan sabbah
## Last update Sun Jul  5 00:37:56 2015 jordan sabbah
##

CC		= g++

RM		= rm -rf

CXXFLAGS	+= -Wall -Wextra -Werror -fPIC
CXXFLAGS	+= -I../../ -I../../../Error -I../../..

LDFLAGS		= -shared -lsfml-system

NAME		= ../../../SOs/lib_API_Thread_SFML.so

SRC		= API_Thread_SFML.cpp		\
		  ../../../Error/Error.cpp

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
