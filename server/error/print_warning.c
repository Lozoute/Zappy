/*
** print_warning.c for Zappy in /home/lks/rendu/PSU_2014_zappy/server
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Tue Jun 16 19:32:07 2015 Thibaud Auzou
** Last update Tue Jun 16 19:32:23 2015 Thibaud Auzou
*/

#include "server.h"

int			print_warning(const char *warning)
{
  fprintf(stderr, "\x1b[1;33m%s\x1b[0m\n", warning);
  return (NOK);
}
