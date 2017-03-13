/*
** states.c for Zappy in /home/lks/rendu/PSU_2014_zappy/server
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Thu Jun 18 18:23:47 2015 Thibaud Auzou
** Last update Thu Jun 18 20:38:36 2015 Thibaud Auzou
*/

#include "server.h"

static int		state(t_wrap_action action)
{
  static int		_state = 1;

  if (action == SET)
    _state = 0;
  return (_state);
}

void			shutdown_server(void)
{
  state(SET);
}

int			server_running(void)
{
  return (state(GET));
}
