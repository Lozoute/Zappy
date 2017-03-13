/*
** teams_destroy.c for Zappy in /home/lks/rendu/PSU_2014_zappy/server/teams
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Wed Jun 17 21:38:31 2015 Thibaud Auzou
** Last update Thu Jun 18 02:27:51 2015 Thibaud Auzou
*/

#include "server.h"

int		team_destroy(void)
{
  return (destroy_list(get_list_teams(), &team_del_func));
}
