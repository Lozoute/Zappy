/*
** teams_list_func.c for Zappy in /home/lks/rendu/PSU_2014_zappy/server
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Wed Jun 17 21:36:44 2015 Thibaud Auzou
** Last update Wed Jul  1 02:45:21 2015 Thibaud Auzou
*/

#include "server.h"

int		team_cmp_func_by_name(void *team1, void *team2)
{
  if (team1 == NULL || team2 == NULL)
    return (0);
  return (!strcmp(((t_team *)team1)->_name, ((t_team *)team2)->_name));
}

int		team_cmp_func_by_name_and_team(void *name, void *team)
{
  if (name == NULL || team == NULL)
    return (0);
  return (!strcmp(name, ((t_team *)team)->_name));
}

int		team_del_func(void *arg)
{
  t_team	*team;

  if (arg == NULL)
    return (ERROR);
  team = (t_team *)(arg);
  destroy_list(&(team->_ceggs), &team_del_egg_func);
  destroy_list(&(team->_eggs), &team_del_egg_func);
  destroy_list(&(team->_members), NULL);
  free(team);
  return (OK);
}

int		team_cmp_egg_by_ptr(void *elem1, void *elem2)
{
  if (!elem1 || !elem2)
    return (0);
  return ((t_egg *)(elem1) == (t_egg *)(elem2));
}

int		team_del_egg_func(void *arg)
{
  if (arg == NULL)
    return (ERROR);
  free((t_egg *)(arg));
  return (OK);
}
