/*
** perror_color.c for zappy in /home/helleg_f/rendu/PSU_2014_zappy/ai/include
** 
** Made by florian hellegouarch
** Login   <helleg_f@epitech.net>
** 
** Started on  Wed Jun 17 16:27:27 2015 florian hellegouarch
** Last update Sun Jul  5 03:22:52 2015 florian hellegouarch
*/

#include "socket.h"

void	perror_color(char const *error)
{
  dprintf(2, ERROR_COLOR);
  perror(error);
  dprintf(2, RESET_COLOR);
}
