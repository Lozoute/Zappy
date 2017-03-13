/*
** cmd_ia_pose.c for Zappy in /home/lks/rendu/PSU_2014_zappy/server
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Tue Jun 30 15:56:08 2015 Thibaud Auzou
** Last update Fri Jul  3 15:03:35 2015 Thibaud Auzou
*/

#include "server.h"

int		cmd_ia_pose(t_socket *sock)
{
  char		*objet;
  t_item_type	item_type;
  t_rock_type	rock_type;

  if (!sock)
    return (log_err("ERROR [NullPtr] [File: %s] [Line: %d]", 0, 0, _F, _L));
  if (!strlen((objet = sock->_buff._args_buff)))
    return (add_msg_to_buffer(&(sock->_buff), KO));
  if (cmd_ia_prend_find_item_type(objet, &item_type, &rock_type) == ERROR)
    return (add_msg_to_buffer(&(sock->_buff), KO));
  return (cmd_ia_pose_item(sock, item_type, rock_type));
}

int		cmd_ia_pose_item(t_socket *sock,
				 t_item_type item_t,
				 t_rock_type rock_t)
{
  t_application	*app;

  if (!sock)
    return (ERROR);
  app = &(sock->_application);
  if ((item_t == FOOD && app->_bag[0] <= 0) ||
      (item_t == ROCK && app->_bag[rock_t + 1] <= 0))
    {
      log_evt("EVENT [Pose Sans Ressources] [%s]",
	      (item_t == FOOD ? "Food" : g_rock_str[rock_t]._name));
      return (add_msg_to_buffer(&(sock->_buff), KO));
    }
  if (item_t == FOOD)
    return (cmd_ia_pose_food(sock));
  else if (item_t == ROCK)
    return (cmd_ia_pose_rock(sock, rock_t));
  return (add_msg_to_buffer(&(sock->_buff), KO));
}

int		cmd_ia_pose_food(t_socket *sock)
{
  t_application	*app;

  if (!sock)
    return (log_err("ERROR [NullPtr] [File: %s] [Line: %d]", 0, 0, _F, _L));
  app = &(sock->_application);
  app->_pv -= PV_RATIO;
  app->_bag[0] = app->_pv / PV_RATIO;
  if (generate_food() == ERROR ||
      board_add_at_coord(app->_x, app->_y, FOOD, NULL) == ERROR)
    return (ERROR);
  cmd_graphic_pose(sock, 0);
  return (add_msg_to_buffer(&(sock->_buff), ROK));
}

int		cmd_ia_pose_rock(t_socket *sock, t_rock_type rock_t)
{
  t_application	*app;
  t_rock	*elem;

  if (!sock)
    return (log_err("ERROR [NullPtr] [File: %s] [Line: %d]", 0, 0, _F, _L));
  app = &(sock->_application);
  (app->_bag[rock_t + 1])--;
  if ((elem = rocks_generate_type(rock_t)) == NULL ||
      board_add_at_coord(app->_x, app->_y, ROCK, elem) == ERROR)
    return (ERROR);
  cmd_graphic_pose(sock, rock_t + 1);
  return (add_msg_to_buffer(&(sock->_buff), ROK));
}
