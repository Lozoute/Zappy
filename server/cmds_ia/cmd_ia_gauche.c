/*
** cmd_ia_gauche.c for Zappy in /home/lks/rendu/PSU_2014_zappy/server
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Mon Jun 29 14:49:46 2015 Thibaud Auzou
** Last update Fri Jul  3 14:05:00 2015 Thibaud Auzou
*/

#include "server.h"

int		cmd_ia_gauche(t_socket *s)
{
  t_application	*a;

  if (!s)
    return (log_err("ERROR [NullPtr] [File: %s] [Line: %d]", 0, 0, _F, _L));
  a = &(s->_application);
  a->_direction = (a->_direction - 1) % 4;
  if (a->_direction < 0)
    a->_direction = LEFT;
  send_msg_graph("ppo %d %d %d %d\n", s->_fd, a->_x, a->_y, a->_direction + 1);
  return (add_msg_to_buffer(&(s->_buff), ROK));
}
