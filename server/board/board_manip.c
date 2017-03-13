/*
** board_manip.c for Zappy in /home/lks/rendu/PSU_2014_zappy/server
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Sat Jun 20 00:17:24 2015 Thibaud Auzou
** Last update Fri Jul  3 14:44:51 2015 Thibaud Auzou
*/

#include "server.h"

t_list		**board_get_at_coord(int x, int y)
{
  t_list	**_board;

  if ((_board = get_board()) == NULL)
    return (NULL);
  while (x < 0)
    x = get_size_x() + x;
  while (y < 0)
    y = get_size_y() + y;
  x %= get_size_x();
  y %= get_size_y();
  return (&(_board[(get_size_x() * y) + x]));
}

int		board_add_at_coord(int x, int y, t_item_type type, void *elem)
{
  t_list	**_case;
  t_item	*new;

  _case = board_get_at_coord(x, y);
  if ((new = malloc(sizeof(t_item))) == NULL)
    return (log_err("ERROR [malloc board_add_at_coord]: ", 1, 1));
  new->_type = type;
  new->_item = elem;
  return (add_to_list_begin(_case, new));
}

int		board_rm_at_coord(int x, int y, void *elem)
{
  t_list	**_case;

  _case = board_get_at_coord(x, y);
  if (rm_from_list(_case, elem, &board_cmp_func_by_item,
		   &board_del_func) == ERROR)
    return (ERROR);
  return (OK);
}

int		board_add_at_random_coord(t_item_type type, void *elem)
{
  int		x;
  int		y;

  board_generate_random_coord(&x, &y, RDM_TOLERANCE);
  if (cmd_graphic_bct_case_everyone(x, y) == ERROR)
    return (ERROR);
  return (board_add_at_coord(x, y, type, elem));
}

void		board_generate_random_coord(int *x, int *y, int tol)
{
  t_list	**tmp;

  *x = rand() % get_size_x();
  *y = rand() % get_size_y();
  if ((tmp = board_get_at_coord(*x, *y)) != NULL && *tmp != NULL && tol > 0)
    board_generate_random_coord(x, y, tol - 1);
}
