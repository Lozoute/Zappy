/*
** board.c for Zappy in /home/lks/rendu/PSU_2014_zappy/server
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Sat Jun 20 00:10:53 2015 Thibaud Auzou
** Last update Tue Jun 23 13:26:12 2015 Thibaud Auzou
*/

#include "server.h"

static t_list		**board(t_wrap_action action)
{
  static t_list		**_board = NULL;

  if (action == DESTROY)
    {
      free(_board);
      _board = NULL;
    }
  else if (action == GET && _board == NULL)
    _board = malloc(sizeof(t_list *) * get_size_x() * get_size_y());
  return (_board);
}

t_list			**get_board(void)
{
  return (board(GET));
}

int			board_init(void)
{
  t_list		**_board;
  int			i;

  if (!(_board = board(GET)))
    return (print_error("ERROR [malloc board init]: ", 1));
  for (i = 0; i < (get_size_x() * get_size_y()); ++i)
    _board[i] = NULL;
  return (OK);
}

void			board_destroy(void)
{
  t_list		**_board;
  int			i;

  if ((_board = board(GET)) != NULL)
    {
      for (i = 0; i < (get_size_x() * get_size_y()); ++i)
	if (_board[i])
	  destroy_list(&(_board[i]), &board_del_func);
      board(DESTROY);
    }
}
