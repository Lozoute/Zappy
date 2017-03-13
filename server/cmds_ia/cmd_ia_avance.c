/*
** cmd_ia_avance.c for Zappy in /home/lks/rendu/PSU_2014_zappy/server
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Fri Jun 26 12:48:30 2015 Thibaud Auzou
** Last update Fri Jul  3 13:59:46 2015 Thibaud Auzou
*/

#include "server.h"

int		cmd_ia_avance(t_socket *s)
{
  t_application	*a;

  if (!s)
    return (log_err("ERROR [NullPtr] [File: %s] [Line: %d]", 0, 0, _F, _L));
  a = &(s->_application);
  if (board_rm_at_coord(a->_x, a->_y, s) == ERROR)
    return (log_err("ERROR [NullPtr] [File: %s] [Line: %d]", 0, 0, _F, _L));
  cmd_ia_avance_update_coord(&(a->_x), &(a->_y), a->_direction);
  if (board_add_at_coord(a->_x, a->_y, PLAYER, s) == ERROR)
    return (ERROR);
  send_msg_graph("ppo %d %d %d %d\n", s->_fd, a->_x, a->_y, a->_direction + 1);
  return (add_msg_to_buffer(&(s->_buff), ROK));
}

void		cmd_ia_avance_update_coord(int *x, int *y, t_direction dir)
{
  if (dir == TOP)
    *y = (*y - 1) % get_size_y();
  else if (dir == RIGHT)
    *x = (*x + 1) % get_size_x();
  else if (dir == BOTTOM)
    *y = (*y + 1) % get_size_y();
  else if (dir == LEFT)
    *x = (*x - 1) % get_size_x();
  while (*x < 0)
    *x = get_size_x() + *x;
  while (*y < 0)
    *y = get_size_y() + *y;
}
