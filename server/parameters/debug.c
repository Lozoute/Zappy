/*
** debug.c for Zappy in /home/lks/rendu/PSU_2014_zappy/server
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Sat Jul  4 19:16:07 2015 Thibaud Auzou
** Last update Sat Jul  4 20:28:19 2015 Thibaud Auzou
*/

#include "server.h"

static int		debug(t_wrap_action action, int val)
{
  static int		_debug = DEFAULT_D;

  if (action == SET)
    _debug |= val;
  return (_debug);
}

int			is_debug(void)
{
  return (debug(GET, 0));
}

void			set_debug(int val)
{
  debug(SET, val);
}

int			check_param_d(char *str)
{
  char			*tmp;
  char			b[BUFF_SIZE];

  if (!str || !(tmp = strstr(str, "=")))
    return (print_error("ERROR NullPtr In Debug Parameter", 0));
  ++tmp;
  if (!(strcmp(tmp, "full")))
    {
      set_debug(DEBUG_SYS);
      set_debug(DEBUG_TEAM);
      set_debug(DEBUG_BOARD);
    }
  else if (!(strcmp(tmp, "teams")))
    set_debug(DEBUG_TEAM);
  else if (!strcmp(tmp, "board"))
    set_debug(DEBUG_BOARD);
  else if (!strcmp(tmp, "sys"))
    set_debug(DEBUG_SYS);
  else
    {
      sprintf(b, "Unknown Debug Parameter: %s", tmp);
      return (print_error(b, 0));
    }
  return (OK);
}
