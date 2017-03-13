##
## Makefile for  in /home/sabbah_j/rendu/TEK2/B4-SystemeUnix/PSU_2014_zappy/zappy_gui/Error
## 
## Made by jordan sabbah
## Login   <sabbah_j@epitech.net>
## 
## Started on  Sat Jul  4 04:41:37 2015 jordan sabbah
## Last update Sat Jul  4 04:43:18 2015 jordan sabbah
##

CC		= g++

RM		= rm -rf

CXXFLAGS	= -Wall -Werror -Wextra -I. -g3 -fPIC
LDFLAGS		= -shared

SRCS		= Error.cpp

OBJS		= $(SRCS:.cpp=.o)

NAME		= ../SOs/lib_API_Error.so

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CXXFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)
clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

