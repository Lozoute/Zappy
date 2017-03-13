/*
** cmd_graphic_pose.c for Zappy in /home/lks/rendu/PSU_2014_zappy/server
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Thu Jul  2 18:24:46 2015 Thibaud Auzou
** Last update Sun Jul  5 18:30:36 2015 florian hellegouarch
*/

#include "server.h"

int		cmd_graphic_pose(t_socket *s, int item)
{
  t_application	*a;
  t_list	**kase;
  int		t[7];

  if (!s || item < 0 || item > 7)
    return (log_err("ERROR [NullPtr] [File: %s] [Line: %d]", 0, 0, _F, _L));
  send_msg_graph("pdr %d %d\n", s->_fd, item);
  a = &(s->_application);
  send_msg_graph("pin %d %d %d %d %d %d %d %d %d %d\n", s->_fd, a->_x, a->_y,
		 a->_bag[0], a->_bag[1], a->_bag[2], a->_bag[3], a->_bag[4],
		 a->_bag[5], a->_bag[6]);
  if (!(kase = board_get_at_coord(a->_x, a->_y)))
    return (log_err("ERROR [NullPtr] [File: %s] [Line: %d]", 0, 0, _F, _L));
  memset(t, 0, sizeof(int) * 7);
  if (cmd_graphic_welcome_case_count(*kase, t) == ERROR)
    return (ERROR);
  send_msg_graph("bct %d %d %d %d %d %d %d %d %d\n",
		 a->_x, a->_y, t[0], t[1], t[2], t[3], t[4], t[5], t[6]);
  return (OK);
}
