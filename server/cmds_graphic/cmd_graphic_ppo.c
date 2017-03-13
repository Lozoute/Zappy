/*
** cmd_graphic_ppo.c for Zappy in /home/lks/rendu/PSU_2014_zappy/server
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Thu Jul  2 15:58:03 2015 Thibaud Auzou
** Last update Fri Jul  3 13:58:08 2015 Thibaud Auzou
*/

#include "server.h"

int		cmd_graphic_ppo(t_socket *sock)
{
  t_socket	*t;
  char		*arg;
  int		id;
  char		b[BUFF_SIZE];
  t_application	*a;

  if (!sock)
    return (log_err("ERROR [NullPtr] [File: %s] [Line: %d]", 0, 0, _F, _L));
  if ((arg = strtok(sock->_buff._args_buff, CMD_SEP)) == NULL)
    return (add_msg_to_buffer(&(sock->_buff), RBAD));
  id = atoi(arg);
  if ((t = get_socket(id)) == NULL)
    return (add_msg_to_buffer(&(sock->_buff), RBAD));
  a = &(t->_application);
  if (t->_socket_type == SERVER || a->_type != IA)
    return (add_msg_to_buffer(&(sock->_buff), RBAD));
  sprintf(b, "ppo %d %d %d %d\n", t->_fd, a->_x, a->_y, a->_direction + 1);
  return (add_msg_to_buffer(&(sock->_buff), b));
}
