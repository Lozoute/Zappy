/*
** cmd_ia_fork.c for Zappy in /home/lks/rendu/PSU_2014_zappy/server
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Wed Jul  1 00:27:00 2015 Thibaud Auzou
** Last update Sat Jul  4 23:18:04 2015 Thibaud Auzou
*/

#include "server.h"

int		cmd_ia_fork(t_socket *sock)
{
  t_egg		*egg;
  static int	id = 0;

  if (!sock || !sock->_application._team)
    return (log_err("ERROR [NullPtr] [File: %s] [Line: %d]", 0, 0, _F, _L));
  if ((egg = malloc(sizeof(t_egg))) == NULL)
    return (log_err("ERROR [malloc cmd_ia_fork]: ", 1, 1));
  egg->_x = sock->_application._x;
  egg->_y = sock->_application._y;
  egg->_ready = 0;
  egg->_delay = 300;
  egg->_pv = 40 * PV_RATIO;
  egg->_id = (++id) % INT_MAX;
  egg->_dad = sock->_fd;
  if (add_to_list_end(&(sock->_application._team->_ceggs), egg) == ERROR)
    return (ERROR);
  if (board_add_at_coord(egg->_x, egg->_y, EGG, egg) == ERROR)
    return (ERROR);
  send_msg_graph("enw %d %d %d %d\n", id, sock->_fd, egg->_x, egg->_y);
  return (add_msg_to_buffer(&(sock->_buff), ROK));
}
