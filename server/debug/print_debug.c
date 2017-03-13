/*
** print_debug.c for Zappy in /home/lks/rendu/PSU_2014_zappy/server
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Sat Jul  4 18:06:10 2015 Thibaud Auzou
** Last update Sat Jul  4 21:31:26 2015 Thibaud Auzou
*/

#include "server.h"

void		print_debug(void)
{
  int		debug;

  debug = is_debug();
  if (debug)
    system("clear");
  if (debug & DEBUG_SYS)
    dump_system();
  if (debug & DEBUG_TEAM)
    dump_teams();
  if (debug & DEBUG_BOARD)
    dump_board();
}
