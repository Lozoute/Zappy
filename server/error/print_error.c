/*
** print_error.c for MyIrc in /home/auzou_t/rendu/PSU_2014_myirc/
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Sun Apr 12 18:34:21 2015 Thibaud Auzou
** Last update Tue Jun 16 19:32:21 2015 Thibaud Auzou
*/

#include "server.h"

int				print_error(const char *error, int option)
{
  fprintf(stderr, "\x1b[1;31m");
  if (!option)
    fprintf(stderr, "%s\n", error);
  else
    perror(error);
  fprintf(stderr, "\x1b[0m");
  return (ERROR);
}
