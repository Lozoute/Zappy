/*
** cmd_ia_expulse.c for Zappy in /home/lks/rendu/PSU_2014_zappy/server
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Tue Jun 30 21:45:13 2015 Thibaud Auzou
** Last update Fri Jul  3 14:04:42 2015 Thibaud Auzou
*/

#include "server.h"

static void	expulsion_msg(int nb, int id)
{
  if (nb == 0)
    send_msg_graph("pex %d\n", id);
}

int		cmd_ia_expulse(t_socket *sock)
{
  t_application	*app;
  t_list	**kase;
  t_list	*it;
  t_list	*cursor;
  t_socket	*vic;
  int		nb;

  if (!sock)
    return (log_err("ERROR [NullPtr] [File: %s] [Line: %d]", 0, 0, _F, _L));
  app = &(sock->_application);
  nb = 0;
  if ((kase = board_get_at_coord(app->_x, app->_y)) == NULL)
    return (log_err("ERROR [NullPtr] [File: %s] [Line: %d]", 0, 0, _F, _L));
  for (it = *kase; it != NULL; it = cursor)
    {
      cursor = it->_next;
      if (it->_elem != NULL && ((t_item *)(it->_elem))->_type == PLAYER
	  && (vic = ((t_item *)(it->_elem))->_item) != NULL && vic != sock)
	{
	  expulsion_msg(nb, sock->_fd);
	  if (cmd_ia_expulse_player(vic, &nb, app->_direction) == ERROR)
	    return (ERROR);
	}
    }
  return (add_msg_to_buffer(&(sock->_buff), (nb <= 0 ? KO : ROK)));
}

int		cmd_ia_expulse_player(t_socket *sock,
				      int *nb,
				      t_direction dir)
{
  t_application	*app;
  char		buff[BUFF_SIZE];

  if (!sock || !nb)
    return (log_err("ERROR [NullPtr] [File: %s] [Line: %d]", 0, 0, _F, _L));
  app = &(sock->_application);
  if (board_rm_at_coord(app->_x, app->_y, sock) == ERROR)
    return (ERROR);
  cmd_ia_avance_update_coord(&(app->_x), &(app->_y), dir);
  if (board_add_at_coord(app->_x, app->_y, PLAYER, sock) == ERROR)
    return (ERROR);
  (*nb)++;
  send_msg_graph("ppo %d %d %d %d\n", sock->_fd, app->_x, app->_y,
		 app->_direction + 1);
  sprintf(buff, "deplacement %d\n", dir + 1);
  return (add_msg_to_buffer(&(sock->_buff), buff));
}
