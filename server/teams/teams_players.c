/*
** teams_players.c for Zapy in /home/lks/rendu/PSU_2014_zappy/server
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Wed Jun 24 14:23:41 2015 Thibaud Auzou
** Last update Sat Jul  4 19:59:28 2015 Thibaud Auzou
*/

#include "server.h"

int		add_player_to_team(t_team *team, t_socket *player)
{
  if (!team || !player)
    return (log_err("ERROR [NullPtr] [File: %s] [Line: %d]", 0, 0, _F, _L));
  if (team->_slots < 1)
    return (log_err("ERROR [TeamFull] [File: %s] [Line: %d]", 0, 0, _F, _L));
  if (add_to_list_begin(&(team->_members), player) == ERROR)
    return (ERROR);
  team->_nb_members++;
  team->_slots--;
  return (OK);
}

int		remove_player_from_team(t_team *team, t_socket *player)
{
  if (!team || !player)
    return (log_err("ERROR [NullPtr] [File: %s] [Line: %d]", 0, 0, _F, _L));
  if (!list_pop(&(team->_members), player, &socket_cmp_func_by_fd))
    return (log_err("ERROR [ElmNotFind] [File: %s] [Line: %d]", 0, 0, _F, _L));
  team->_slots++;
  team->_nb_members--;
  return (OK);
}
