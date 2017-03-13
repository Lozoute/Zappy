/*
** sigint.c for Zappy in /home/lks/rendu/PSU_2014_zappy/server
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Fri Jul  3 23:57:04 2015 Thibaud Auzou
** Last update Sat Jul  4 00:09:09 2015 Thibaud Auzou
*/

#include "server.h"

void		sigint(int sig)
{
  if (sig == SIGINT)
    log_err("SIGINT: Shutdown", 0, 0);
  clean_everything();
  shutdown_server();
  exit(EXIT_SUCCESS);
}
