/*
** cmd_graphic_welcome_players.c for Zappy in /home/lks/rendu/PSU_2014_zappy/
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Thu Jul  2 12:51:02 2015 Thibaud Auzou
** Last update Fri Jul  3 13:56:00 2015 Thibaud Auzou
*/

#include "server.h"

int		cmd_graphic_welcome_players(t_socket *sock)
{
  t_list	**sockets;
  t_list	*it;
  t_socket	*p;
  t_application	*app;
  char		b[BUFF_SIZE * 2];

  if (!sock || !(sockets = get_list_socket()))
    return (log_err("ERROR [NullPtr] [File: %s] [Line: %d]", 0, 0, _F, _L));
  for (it = *sockets; it; it = it->_next)
    if ((p = it->_elem) && p->_socket_type == CLIENT)
      if ((app = &(p->_application)) && app->_team && app->_type == IA)
	{
	  sprintf(b, "pnw %d %d %d %d %d %s\n", p->_fd, app->_x, app->_y,
		  app->_direction + 1, app->_lvl, app->_team->_name);
	  if (add_msg_to_buffer(&(sock->_buff), b) == ERROR)
	    return (ERROR);
	}
  return (OK);
}
