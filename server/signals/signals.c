/*
** signals.c for Zappy in /home/lks/rendu/PSU_2014_zappy/server
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Sat Jul  4 00:00:30 2015 Thibaud Auzou
** Last update Sat Jul  4 01:10:00 2015 Thibaud Auzou
*/

#include "server.h"

int			signals_init(void)
{
  struct sigaction	act;

  memset(&act, 0, sizeof(act));
  act.sa_handler = &sigint;
  if (sigaction(SIGINT, &act, NULL) == ERROR)
    return (print_error("ERROR [sigaction signals_init]: ", 1));
  return (OK);
}
