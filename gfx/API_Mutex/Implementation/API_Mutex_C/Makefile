##
## Makefile for  in /home/sabbah_j/rendu/TEK2/B4-SystemeUnix/PSU_2014_zappy/API_Mutex/Implemantation/API_Mutex_STD
## 
## Made by jordan sabbah
## Login   <sabbah_j@epitech.net>
## 
## Started on  Sun Jun  7 16:31:19 2015 jordan sabbah
## Last update Sat Jul  4 17:15:19 2015 jordan sabbah
##

CC		= g++

RM		= rm -rf

CXXFLAGS	= -Wall -Wextra -Werror -fPIC -I../.. -I../../../Error
CXXFLAGS	+= -I.

LDFLAGS		= -shared -lpthread -l_API_Error -L../../../SOs -Wl,-rpath=../../../SOs/
LDFLAGS		+= -Wl,-rpath=../../zappy_gui/SOs
LDFLAGS		+= -Wl,-rpath=../../zappy_gui/API_Mutex/Implementation/API_Mutex_C

NAME		= ../../../SOs/lib_API_Mutex_C.so

SRC		= API_Mutex_C.cpp	\
		  API_MutexCond_C.cpp	\
		  ../../ScopedLock.cpp

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
