/*
** dump_system.c for Zappy in /home/lks/rendu/PSU_2014_zappy/server
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Sat Jul  4 20:45:57 2015 Thibaud Auzou
** Last update Sat Jul  4 21:31:39 2015 Thibaud Auzou
*/

#include "server.h"

void				dump_system(void)
{
  char				b[4096];
  double			delta;
  LLU				avg;

  delta = (double)(cycle_delta(GET, 0)) / (double)(get_ucycle()) * 100.0;
  avg = (LLU)(get_average_cycle(GET, 0));
  sprintf(b, "##########   ZAPPY SERVER   ##########\n");
  sprintf(b + strlen(b), "[Port: %d] [Size X: %d] ", get_port(), get_size_x());
  sprintf(b + strlen(b), "[Size Y: %d] ", get_size_y());
  sprintf(b + strlen(b), "[Max Player Per Team: %d] ", get_number_client());
  sprintf(b + strlen(b), "[Frequency: %d]\n", get_time());
  sprintf(b + strlen(b), "---------- CYCLES ----------\n");
  sprintf(b + strlen(b), "[Cycle: %llu usec] ", (LLU)(get_ucycle()));
  sprintf(b + strlen(b), "[Select Time: %llu]\n", (LLU)(get_cycle()->tv_usec));
  sprintf(b + strlen(b), "[Nb Of Cycles: %llu]", (LLU)(get_cycle_number(GET)));
  sprintf(b + strlen(b), "[Average Cycle: %llu]\n", avg);
  sprintf(b + strlen(b), "[Cycle Delta: %llu]", (LLU)(cycle_delta(GET, 0)));
  sprintf(b + strlen(b), "[%g%%]\n", delta);
  printf("%s", b);
}
