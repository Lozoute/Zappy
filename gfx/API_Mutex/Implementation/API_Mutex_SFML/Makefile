##
## Makefile for  in /home/sabbah_j/rendu/TEK2/B4-SystemeUnix/PSU_2014_zappy/API_Mutex/Implemantation/API_Mutex_STD
## 
## Made by jordan sabbah
## Login   <sabbah_j@epitech.net>
## 
## Started on  Sun Jun  7 16:31:19 2015 jordan sabbah
## Last update Sun Jul  5 00:37:11 2015 jordan sabbah
##

CC		= g++

RM		= rm -rf

CXXFLAGS	+= -Wall -Wextra -Werror -fPIC -I../.. -I../../../Error -I../../..

LDFLAGS		= -shared -lsfml-system

NAME		= ../../../SOs/lib_API_Mutex_SFML.so

SRC		= API_Mutex_SFML.cpp	\
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
