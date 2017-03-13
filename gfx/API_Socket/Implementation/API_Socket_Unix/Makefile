##
## Makefile for  in /home/sabbah_j/rendu/TEK2/B4-SystemeUnix/PSU_2014_zappy/API_Socket/Implementation/API_Socket_Unix
## 
## Made by jordan sabbah
## Login   <sabbah_j@epitech.net>
## 
## Started on  Sun Jun  7 12:47:54 2015 jordan sabbah
## Last update Sat Jul  4 04:53:07 2015 jordan sabbah
##

CC		= g++

RM		= rm -rf

CXXFLAGS	+= -Wall -Wextra -Werror -fPIC -I../../../Error -I../..

LDFLAGS		= -shared -l_API_Error -L../../../SOs -Wl,-rpath=../../../SOs/

NAME		= ../../../SOs/lib_API_Socket_Unix.so

SRC		= API_Socket_Unix.cpp
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
