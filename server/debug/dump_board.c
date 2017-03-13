/*
** dump_board.c for Zappy in /home/lks/rendu/PSU_2014_zappy/server
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Sat Jul  4 21:31:11 2015 Thibaud Auzou
** Last update Sat Jul  4 21:48:13 2015 Thibaud Auzou
*/

#include "server.h"

static void			dump_case(t_list *kase)
{
  t_item			*elem;
  t_list			*it;
  int				j;

  if (!kase)
    return;
  for (j = 0, it = kase; it; it = it->_next, ++j);
  printf("\x1b[1;3");
  it = kase;
  if ((elem = it->_elem) && elem->_type == ROCK)
    printf("3m[%d]\x1b[0m", j);
  else if (elem && elem->_type == FOOD)
    printf("2m[%d]\x1b[0m", j);
  else if (elem && elem->_type == EGG)
    {
      if (elem->_item && ((t_egg *)(elem->_item))->_ready)
	printf("4m[%d]\x1b[0m", j);
      else
	printf("5m[%d]\x1b[0m", j);
    }
  else
    printf("1m[%d]\x1b[0m", j);
}

static void			dump_title(void)
{
  int				i;

  for (i = 0; i < (get_size_x() * 3 - (int)strlen("BOARD")) / 2; ++i)
    printf("#");
  printf("BOARD");
  for (i = 0; i < (get_size_x() * 3 - (int)strlen("BOARD")) / 2; ++i)
    printf("#");
  printf("\n");
}

void				dump_board(void)
{
  t_list			**board;
  int				i;
  int				k;

  if (!(board = get_board()))
    return;
  dump_title();
  for (k = 0, i = 0; i < (get_size_x() * get_size_y()); ++i, ++k)
    {
      if (k >= get_size_x())
	{
	  k = 0;
	  printf("\n");
	}
      if (board[i])
	dump_case(board[i]);
      else
	printf("[0]");
    }
  printf("\n");
}
