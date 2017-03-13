/*
** cmd_ia_incantation_raise.c for Zappy in /home/lks/rendu/PSU_2014_zappy/server
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Wed Jul  1 19:47:03 2015 Thibaud Auzou
** Last update Fri Jul  3 14:23:20 2015 Thibaud Auzou
*/

#include "server.h"

int		cmd_ia_incantation_raise_player(t_socket *sock, int ok)
{
  t_application	*app;
  char		buff[BUFF_SIZE];

  if (!sock)
    return (log_err("ERROR [NullPtr] [File: %s] [Line: %d]", 0, 0, _F, _L));
  app = &(sock->_application);
  if (ok)
    app->_lvl++;
  sprintf(buff, "niveau actuel : %d\n", app->_lvl);
  send_msg_graph("plv %d %d\n", sock->_fd, app->_lvl);
  return (add_msg_to_buffer(&(sock->_buff), buff));
}

int		cmd_ia_incantation_raise_rock(int x,
					      int y,
					      t_rock *rock,
					      int ok)
{
  if (ok)
    {
      if (!rock)
	return (log_err("ERR [NullPtr] [File: %s] [Line: %d]", 0, 0, _F, _L));
      if (board_rm_at_coord(x, y, rock) == ERROR)
	return (ERROR);
      rocks_delete(rock);
    }
  return (OK);
}
