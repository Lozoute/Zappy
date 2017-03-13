##
## Makefile for ZAppy in /home/auzou_t/rendu/PSU_2014_zappy
## 
## Made by Thibaud Auzou
## Login   <auzou_t@epitech.net>
## 
## Started on  Sun Jul  5 21:19:53 2015 Thibaud Auzou
## Last update Sun Jul  5 22:15:21 2015 Thibaud Auzou
##

CC		= gcc

CCPP		= g++

RM		= rm -rf

CFLAGS		+= -Wall -Wextra -Werror
CFLAGS		+= -I./server/include/ -I../include/ -I../../include/
CFLAGS		+= -I./ai/include

CXXFLAGS	+= -Wall -Wextra -Werror
CXXFLAGS	+= -I./include -I./ai/include
CXXFLAGS	+= -std=c++11

LDFLAGS		+= -pthread

## SERVER ##
S_NAME		= zappy_server

S_SRC		= server/server.c \
		  server/signals/signals.c \
		  server/signals/sigint.c \
		  server/error/print_error.c \
		  server/error/print_warning.c \
		  server/error/log_error.c \
		  server/error/log_file.c \
		  server/debug/print_debug.c \
		  server/debug/dump_system.c \
		  server/debug/dump_teams.c \
		  server/debug/dump_board.c \
		  server/parameters/parameters.c \
		  server/parameters/port.c \
		  server/parameters/size_x.c \
		  server/parameters/size_y.c \
		  server/parameters/number_client.c \
		  server/parameters/time.c \
		  server/parameters/team_param.c \
		  server/parameters/debug.c \
		  server/monitoring/monitoring.c \
		  server/states/states.c \
		  server/list/list.c \
		  server/list/list_manip.c \
		  server/socket/socket.c \
		  server/socket/socket_server.c \
		  server/socket/socket_client.c \
		  server/socket/socket_list_func.c \
		  server/socket/socket_destroy.c \
		  server/teams/teams.c \
		  server/teams/teams_players.c \
		  server/teams/teams_destroy.c \
		  server/teams/teams_list_func.c \
		  server/teams/teams_eggs.c \
		  server/buffer/buffer.c \
		  server/buffer/buffer_msg.c \
		  server/buffer/buffer_list_func.c \
		  server/application/application.c \
		  server/application/application_ia.c \
		  server/application/application_graphic.c \
		  server/application/exec_list_func.c \
		  server/board/board.c \
		  server/board/board_manip.c \
		  server/board/board_list_func.c \
		  server/rocks/rocks.c \
		  server/rocks/rocks_count.c \
		  server/rocks/rocks_list_func.c \
		  server/rocks/rocks_gen.c \
		  server/food/food.c \
		  server/food/food_count.c \
		  server/cycle/cycle.c \
		  server/cycle/cycle_timer.c \
		  server/cycle/cycle_delta.c \
		  server/graphic/graphic.c \
		  server/cmds_ia/cmd_ia_avance.c \
		  server/cmds_ia/cmd_ia_droite.c \
		  server/cmds_ia/cmd_ia_gauche.c \
		  server/cmds_ia/cmd_ia_voir.c \
		  server/cmds_ia/cmd_ia_inventaire.c \
		  server/cmds_ia/cmd_ia_prend.c \
		  server/cmds_ia/cmd_ia_pose.c \
		  server/cmds_ia/cmd_ia_expulse.c \
		  server/cmds_ia/cmd_ia_broadcast.c \
		  server/cmds_ia/cmd_ia_broadcast_calc.c \
		  server/cmds_ia/cmd_ia_connect_nbr.c \
		  server/cmds_ia/cmd_ia_fork.c \
		  server/cmds_ia/cmd_ia_incantation.c \
		  server/cmds_ia/cmd_ia_incantation_raise.c \
		  server/cmds_ia/tab_elevation.c \
		  server/cmds_ia/cmd_ia_death.c \
		  server/cmds_ia/cmd_ia_victory.c \
		  server/cmds_graphic/cmd_graphic_welcome.c \
		  server/cmds_graphic/cmd_graphic_welcome_cases.c \
		  server/cmds_graphic/cmd_graphic_welcome_teams.c \
		  server/cmds_graphic/cmd_graphic_welcome_players.c \
		  server/cmds_graphic/cmd_graphic_welcome_eggs.c \
		  server/cmds_graphic/cmd_graphic_msz.c \
		  server/cmds_graphic/cmd_graphic_bct.c \
		  server/cmds_graphic/cmd_graphic_mct.c \
		  server/cmds_graphic/cmd_graphic_tna.c \
		  server/cmds_graphic/cmd_graphic_ppo.c \
		  server/cmds_graphic/cmd_graphic_plv.c \
		  server/cmds_graphic/cmd_graphic_pin.c \
		  server/cmds_graphic/cmd_graphic_sgt.c \
		  server/cmds_graphic/cmd_graphic_sst.c \
		  server/cmds_graphic/cmd_graphic_prend.c \
		  server/cmds_graphic/cmd_graphic_pose.c

S_OBJS		= $(S_SRC:.c=.o)

## AI ##
AI_NAME		= zappy_ai

AI_SRCS		= ai/Client.cpp				\
		  ai/Protocol.cpp			\
		  ai/Player.cpp				\
		  ai/ProtocolParser.cpp			\
		  ai/Random.cpp				\
		  ai/Fork.cpp				\
		  ai/Level.cpp				\
		  ai/Inventory.cpp			\
		  ai/View.cpp				\
		  ai/Broadcast.cpp			\
		  ai/IaClientException.cpp		\
		  ai/ConnectionException.cpp		\
		  ai/main.cpp

FOLDER_SOCK	= ai/c_socket

SRCS_SOCK	= $(FOLDER_SOCK)/socket_init.c		\
		  $(FOLDER_SOCK)/socket_close.c		\
		  $(FOLDER_SOCK)/perror_color.c		\
		  $(FOLDER_SOCK)/get_char.c		\
		  $(FOLDER_SOCK)/write_line.c

AI_COBJS	= $(SRCS_SOCK:.c=.o)

AI_OBJS		= $(AI_SRCS:.cpp=.o)

G_NAME		= zappy_gfx


all:		$(S_NAME) $(AI_NAME) $(G_NAME)

$(S_NAME):	$(S_OBJS)
		$(CC) $(S_OBJS) -o $(S_NAME)

$(AI_NAME):	$(AI_COBJS) $(AI_OBJS)
		$(CCPP) -o $(AI_NAME) $(AI_COBJS) $(AI_OBJS) $(LDFLAGS)

$(G_NAME):
		make -C gfx/


clean:
		$(RM) $(S_OBJS)
		$(RM) $(AI_OBJS) $(AI_COBJS)
		make clean -C gfx/

fclean:		clean
		$(RM) $(S_NAME)
		$(RM) $(AI_NAME)
		make fclean -C gfx/

re:		fclean all

.PHONY:		all clean fclean re
