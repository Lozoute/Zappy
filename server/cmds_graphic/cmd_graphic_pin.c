/*
** cmd_graphic_pin.c for Zappy in /home/lks/rendu/PSU_2014_zappy/server
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Thu Jul  2 16:15:25 2015 Thibaud Auzou
** Last update Fri Jul  3 13:58:44 2015 Thibaud Auzou
*/

#include "server.h"

int		cmd_graphic_pin(t_socket *sock)
{
  t_socket	*t;
  char		*arg;
  int		id;

  if (!sock)
    return (log_err("ERROR [NullPtr] [File: %s] [Line: %d]", 0, 0, _F, _L));
  if ((arg = strtok(sock->_buff._args_buff, CMD_SEP)) == NULL)
    return (add_msg_to_buffer(&(sock->_buff), RBAD));
  id = atoi(arg);
  if ((t = get_socket(id)) == NULL)
    return (add_msg_to_buffer(&(sock->_buff), RBAD));
  return (cmd_graphic_pin_player(t, sock));
}

int		cmd_graphic_pin_player(t_socket *player, t_socket *sock)
{
  t_application	*a;
  char		b[BUFF_SIZE];

  if (!sock || !player)
    return (log_err("ERROR [NullPtr] [File: %s] [Line: %d]", 0, 0, _F, _L));
  a = &(player->_application);
  sprintf(b, "pin %d %d %d %d %d %d %d %d %d %d\n", player->_fd, a->_x, a->_y,
	  a->_bag[0], a->_bag[1], a->_bag[2], a->_bag[3], a->_bag[4],
	  a->_bag[5], a->_bag[6]);
  return (add_msg_to_buffer(&(sock->_buff), b));
}
