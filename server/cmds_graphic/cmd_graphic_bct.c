/*
** cmd_graphic_bct.c for Zappy in /home/lks/rendu/PSU_2014_zappy/server
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Thu Jul  2 15:37:22 2015 Thibaud Auzou
** Last update Fri Jul  3 13:55:14 2015 Thibaud Auzou
*/

#include "server.h"

int		cmd_graphic_bct(t_socket *sock)
{
  char		*arg;
  int		x;
  int		y;

  if (!sock)
    return (log_err("ERROR [NullPtr] [File: %s] [Line: %d]", 0, 0, _F, _L));
  if ((arg = strtok(sock->_buff._args_buff, CMD_SEP)) == NULL)
    return (add_msg_to_buffer(&(sock->_buff), RBAD));
  if ((x = atoi(arg)) < 0 || x >= get_size_x())
    return (add_msg_to_buffer(&(sock->_buff), RBAD));
  if ((arg = strtok(NULL, CMD_SEP)) == NULL)
    return (add_msg_to_buffer(&(sock->_buff), RBAD));
  if ((y = atoi(arg)) < 0 || y >= get_size_y())
    return (add_msg_to_buffer(&(sock->_buff), RBAD));
  return (cmd_graphic_bct_case(sock, x, y));
}

int		cmd_graphic_bct_case(t_socket *sock, int x, int y)
{
  t_list	**kase;
  int		t[7];
  char		b[BUFF_SIZE];

  if (!sock || !(kase = board_get_at_coord(x, y)))
    return (log_err("ERROR [NullPtr] [File: %s] [Line: %d]", 0, 0, _F, _L));
  memset(t, 0, sizeof(int) * 7);
  if (cmd_graphic_welcome_case_count(*kase, t) == ERROR)
    return (ERROR);
  sprintf(b, "bct %d %d %d %d %d %d %d %d %d\n",
	  x, y, t[0], t[1], t[2], t[3], t[4], t[5], t[6]);
  if (add_msg_to_buffer(&(sock->_buff), b) == ERROR)
    return (ERROR);
  return (OK);
}

int		cmd_graphic_bct_case_everyone(int x, int y)
{
  t_list	**kase;
  int		t[7];

  if (!(kase = board_get_at_coord(x, y)))
    return (log_err("ERROR [NullPtr] [File: %s] [Line: %d]", 0, 0, _F, _L));
  memset(t, 0, sizeof(int) * 7);
  if (cmd_graphic_welcome_case_count(*kase, t) == ERROR)
    return (ERROR);
  send_msg_graph("bct %d %d %d %d %d %d %d %d %d\n",
		 x, y, t[0], t[1], t[2], t[3], t[4], t[5], t[6]);
  return (OK);
}
