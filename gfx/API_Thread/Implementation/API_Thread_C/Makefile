##
## Makefile for  in /home/sabbah_j/rendu/TEK2/B4-SystemeUnix/PSU_2014_zappy/API_Thread/Implementation/API_Thread_STD
## 
## Made by jordan sabbah
## Login   <sabbah_j@epitech.net>
## 
## Started on  Sun Jun  7 17:00:38 2015 jordan sabbah
## Last update Sat Jul  4 17:17:50 2015 jordan sabbah
##

CC		= g++

RM		= rm -rf

CXXFLAGS	+= -Wall -Wextra -Werror -fPIC
CXXFLAGS	+= -I../../ -I../../../Error

LDFLAGS		= -shared -lpthread -l_API_Error -L../../../SOs -Wl,-rpath=../../../SOs/
LDFLAGS		+= -Wl,-rpath=../../zappy_gui/SOs
LDFLAGS		+= -Wl,-rpath=../../zappy_gui/API_Thread/Implementation/API_Thread_C

NAME		= ../../../SOs/lib_API_Thread_C.so

SRC		= API_Thread_C.cpp

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
