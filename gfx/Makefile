##
## Makefile for  in /home/sabbah_j/rendu/TEK2/B4-SystemeUnix/PSU_2014_zappy
## 
## Made by jordan sabbah
## Login   <sabbah_j@epitech.net>
## 
## Started on  Sun Jun  7 17:16:20 2015 jordan sabbah
## Last update Sun Jul  5 08:43:36 2015 jordan sabbah
##

CC		= g++

RM		= rm -rf

MAKE		= make -C

CXXFLAGS	= -Wall -Wextra -Werror -std=c++11
CXXFLAGS	+= -IAPI_Client -IAPI_Loader
CXXFLAGS	+= -IAPI_GUI -IError -IAPI_Protocol
CXXFLAGS	+= -IAPI_Socket -IAPI_Thread -IAPI_Mutex
CXXFLAGS	+= -I./API_Thread/Implementation/API_Thread_C
CXXFLAGS	+= -I./API_Mutex/Implementation/API_Mutex_C
CXXFLAGS	+= -I./API_Socket/Implementation/API_Socket_Unix
CXXFLAGS	+= -I./API_Socket

LDFLAGS		= -ldl -l_API_Error
LDFLAGS		+= -L./API_Client -Wl,-rpath=./API_Client
LDFLAGS		+= -l_API_Client -l_API_Protocol -L./SOs -Wl,-rpath=./SOs
LDFLAGS		+= -l_API_Error -l_API_GUI_SFML -l_API_Mutex_C
LDFLAGS		+= -l_API_Socket_Unix  -l_API_Thread_C
LDFLAGS		+= -Wl,-rpath=./gfx/SOs
LDFLAGS		+= -Wl,-rpath=./gfx/API_Client

NAME		= ../zappy_gfx

SRCS		= main.cpp			\
		  Parser.cpp

OBJS		= $(SRCS:.cpp=.o)


all: libs $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(CXXFLAGS) $(LDFLAGS) -o $(NAME)

libs:
	$(MAKE) Error all
	$(MAKE) API_Mutex/Implementation/API_Mutex_SFML all
	$(MAKE) API_Mutex/Implementation/API_Mutex_C all
	$(MAKE) API_Thread/Implementation/API_Thread_SFML all
	$(MAKE) API_Thread/Implementation/API_Thread_C all
	$(MAKE) API_Socket/Implementation/API_Socket_Unix all
	$(MAKE) API_Protocol all
	$(MAKE) API_GUI all
	$(MAKE) API_Client/ all

clean:
	$(MAKE) Error clean
	$(MAKE) API_Mutex/Implementation/API_Mutex_SFML clean
	$(MAKE) API_Mutex/Implementation/API_Mutex_C clean
	$(MAKE) API_Thread/Implementation/API_Thread_SFML clean
	$(MAKE) API_Thread/Implementation/API_Thread_C clean
	$(MAKE) API_Socket/Implementation/API_Socket_Unix clean
	$(MAKE) API_Protocol clean
	$(MAKE) API_GUI clean
	$(MAKE) API_Client/ clean
	$(RM) $(OBJS)

fclean: clean
	$(MAKE) Error fclean
	$(MAKE) API_Mutex/Implementation/API_Mutex_SFML fclean
	$(MAKE) API_Mutex/Implementation/API_Mutex_C fclean
	$(MAKE) API_Thread/Implementation/API_Thread_SFML fclean
	$(MAKE) API_Thread/Implementation/API_Thread_C fclean
	$(MAKE) API_Socket/Implementation/API_Socket_Unix fclean
	$(MAKE) API_Protocol fclean
	$(MAKE) API_GUI fclean
	$(MAKE) API_Client/ fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
