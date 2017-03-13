##
## Makefile for Zappy in /home/lks/rendu/PSU_2014_zappy/server
## 
## Made by Thibaud Auzou
## Login   <auzou_t@epitech.net>
## 
## Started on  Tue Jun 16 15:46:03 2015 Thibaud Auzou
## Last update Sun Jul  5 21:19:16 2015 Thibaud Auzou
##

CC			= gcc

RM			= rm -rf

CFLAGS			+= -Wall -Wextra -Werror
CFLAGS			+= -I./include/ -I../include/ -I../../include/

LDFLAGS			+=

NAME			= ../zappy_server

SRC			= server.c \
			  signals/signals.c \
			  signals/sigint.c \
			  error/print_error.c \
			  error/print_warning.c \
			  error/log_error.c \
			  error/log_file.c \
			  debug/print_debug.c \
			  debug/dump_system.c \
			  debug/dump_teams.c \
			  debug/dump_board.c \
			  parameters/parameters.c \
			  parameters/port.c \
			  parameters/size_x.c \
			  parameters/size_y.c \
			  parameters/number_client.c \
			  parameters/time.c \
			  parameters/team_param.c \
			  parameters/debug.c \
			  monitoring/monitoring.c \
			  states/states.c \
			  list/list.c \
			  list/list_manip.c \
			  socket/socket.c \
			  socket/socket_server.c \
			  socket/socket_client.c \
			  socket/socket_list_func.c \
			  socket/socket_destroy.c \
			  teams/teams.c \
			  teams/teams_players.c \
			  teams/teams_destroy.c \
			  teams/teams_list_func.c \
			  teams/teams_eggs.c \
			  buffer/buffer.c \
			  buffer/buffer_msg.c \
			  buffer/buffer_list_func.c \
			  application/application.c \
			  application/application_ia.c \
			  application/application_graphic.c \
			  application/exec_list_func.c \
			  board/board.c \
			  board/board_manip.c \
			  board/board_list_func.c \
			  rocks/rocks.c \
			  rocks/rocks_count.c \
			  rocks/rocks_list_func.c \
			  rocks/rocks_gen.c \
			  food/food.c \
			  food/food_count.c \
			  cycle/cycle.c \
			  cycle/cycle_timer.c \
			  cycle/cycle_delta.c \
			  graphic/graphic.c \
			  cmds_ia/cmd_ia_avance.c \
			  cmds_ia/cmd_ia_droite.c \
			  cmds_ia/cmd_ia_gauche.c \
			  cmds_ia/cmd_ia_voir.c \
			  cmds_ia/cmd_ia_inventaire.c \
			  cmds_ia/cmd_ia_prend.c \
			  cmds_ia/cmd_ia_pose.c \
			  cmds_ia/cmd_ia_expulse.c \
			  cmds_ia/cmd_ia_broadcast.c \
			  cmds_ia/cmd_ia_broadcast_calc.c \
			  cmds_ia/cmd_ia_connect_nbr.c \
			  cmds_ia/cmd_ia_fork.c \
			  cmds_ia/cmd_ia_incantation.c \
			  cmds_ia/cmd_ia_incantation_raise.c \
			  cmds_ia/tab_elevation.c \
			  cmds_ia/cmd_ia_death.c \
			  cmds_ia/cmd_ia_victory.c \
			  cmds_graphic/cmd_graphic_welcome.c \
			  cmds_graphic/cmd_graphic_welcome_cases.c \
			  cmds_graphic/cmd_graphic_welcome_teams.c \
			  cmds_graphic/cmd_graphic_welcome_players.c \
			  cmds_graphic/cmd_graphic_welcome_eggs.c \
			  cmds_graphic/cmd_graphic_msz.c \
			  cmds_graphic/cmd_graphic_bct.c \
			  cmds_graphic/cmd_graphic_mct.c \
			  cmds_graphic/cmd_graphic_tna.c \
			  cmds_graphic/cmd_graphic_ppo.c \
			  cmds_graphic/cmd_graphic_plv.c \
			  cmds_graphic/cmd_graphic_pin.c \
			  cmds_graphic/cmd_graphic_sgt.c \
			  cmds_graphic/cmd_graphic_sst.c \
			  cmds_graphic/cmd_graphic_prend.c \
			  cmds_graphic/cmd_graphic_pose.c

OBJS			= $(SRC:.c=.o)


all: $(NAME)

$(NAME): $(OBJS)
			$(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

clean:
			$(RM) $(OBJS)

fclean: clean
			$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
