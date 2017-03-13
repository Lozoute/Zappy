/*
** cmd_graphic_welcome_cases.c for Zappy in /home/lks/rendu/PSU_2014_zappy/serv
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Thu Jul  2 12:49:35 2015 Thibaud Auzou
** Last update Fri Jul  3 13:56:55 2015 Thibaud Auzou
*/

#include "server.h"

int		cmd_graphic_welcome_cases(t_socket *sock)
{
  t_list	**board;
  char		b[BUFF_SIZE];
  int		t[7];
  int		i;

  if (!sock || !(board = get_board()))
    return (log_err("ERROR [NullPtr] [File: %s] [Line: %d]", 0, 0, _F, _L));
  for (i = 0; i < get_size_x() * get_size_y(); ++i)
    {
      memset(t, 0, sizeof(int) * 7);
      if (cmd_graphic_welcome_case_count(board[i], t) == ERROR)
	return (ERROR);
      sprintf(b, "bct %d %d %d %d %d %d %d %d %d\n",
	      i % get_size_x(), i / get_size_x(), t[0], t[1], t[2], t[3],
	      t[4], t[5], t[6]);
      if (add_msg_to_buffer(&(sock->_buff), b) == ERROR)
	return (ERROR);
    }
  return (OK);
}

int		cmd_graphic_welcome_case_count(t_list *it, int *t)
{
  t_item	*item;

  if (!t)
    return (log_err("ERROR [NullPtr] [File: %s] [Line: %d]", 0, 0, _F, _L));
  for (; it != NULL; it = it->_next)
    if ((item = it->_elem))
      {
	if (item->_type == FOOD)
	  t[0]++;
	else if (item->_type == ROCK && item->_item)
	  t[((t_rock *)(item->_item))->_type + 1]++;
      }
  return (OK);
}
