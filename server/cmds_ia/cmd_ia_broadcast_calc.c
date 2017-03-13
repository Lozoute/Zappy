/*
** cmd_ia_broadcast_calc.c for Zappy in /home/lks/rendu/PSU_2014_zappy/server
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Fri Jul  3 00:08:59 2015 Thibaud Auzou
** Last update Fri Jul  3 14:00:51 2015 Thibaud Auzou
*/

#include "server.h"

int		cmd_ia_broadcast_calc(t_application *sender,
				      t_application *rec)
{
  int		x;
  int		y;

  if (!sender || !rec)
    return (log_err("ERROR [NullPtr] [File: %s] [Line: %d]", 0, 0, _F, _L));
  x = cmd_ia_broadcast_dist(rec->_x, sender->_x, get_size_x());
  y = cmd_ia_broadcast_dist(rec->_y, sender->_y, get_size_y());
  if (y < 0 && x < 0 && 10 * x / y > 3 && 10 * y / x > 3)
    return (2);
  if (y < 0 && -3 <= 10 * x / y && 10 * x / y <= 3)
    return (1);
  if (y < 0 && x > 0 && 10 * x / y < -3 && 10 * y / x < -3)
    return (8);
  if (y > 0 && x < 0 && 10 * x / y < -3 && 10 * y / x < -3)
    return (4);
  if (y > 0 && -3 <= 10 * x / y && 10 * x / y <= 3)
    return (5);
  if (y > 0 && x > 0 && 10 * x / y > 3 && 10 * y / x > 3)
    return (6);
  if (x < 0)
    return (3);
  if (x > 0)
    return (7);
  return (0);
}

int		cmd_ia_broadcast_min_abs(int x1, int x2)
{
  int		x_abs1;
  int		x_abs2;

  x_abs1 = x1 > 0 ? x1 : -x1;
  x_abs2 = x2 > 0 ? x2 : -x2;
  if (x_abs1 < x_abs2)
    return (x1);
  return (x2);
}

int		cmd_ia_broadcast_dist(int x_from, int x_to, int size_x)
{
  int		dist_left;
  int		dist_right;
  int		diff;

  diff = x_to - x_from;
  dist_left = diff <= 0 ? diff : diff - size_x;
  dist_right = diff >= 0 ? diff : diff + size_x;
  return (cmd_ia_broadcast_min_abs(dist_left, dist_right));
}

int		cmd_ia_broadcast_relative(int dir, t_application *target)
{
  if (!target)
    return (log_err("ERROR [NullPtr] [File: %s] [Line: %d]", 0, 0, _F, _L));
  if (dir == 0)
    return (0);
  dir = dir + (target->_direction * 2);
  if (dir > 8)
    dir %= 8;
  return (dir);
}
