/*
** server.c for Zappy in /home/lks/rendu/PSU_2014_zappy/server
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Tue Jun 16 15:49:27 2015 Thibaud Auzou
** Last update Sat Jul  4 18:07:41 2015 Thibaud Auzou
*/

#include "server.h"

int				main(int argc, char **argv)
{
  if (argc < NB_PARAM || argv == NULL)
    return (print_error(USAGE_SERVER, 0));
  else if (check_parameters(argc, argv) != OK)
    return (ERROR);
  return (start_server());
}

int				start_server(void)
{
  t_socket			*server;
  int				fd_server;

  srand(time(0) % UINT_MAX);
  if (signals_init() == ERROR)
    return (ERROR);
  if (board_init() == ERROR)
    return (print_error("ERROR : Unable To Init Board.", 0));
  if (log_file_init() == NULL)
    return (print_error("ERROR : Unable To Init LogFile.", 0));
  if ((fd_server = start_listening(get_port())) == ERROR)
    return (print_error("ERROR : Unable To Init Server Socket.", 0));
  if ((server = create_socket(SERVER, fd_server)) == NULL)
    return (print_error("ERROR : Unable To Initialize Server.", 0));
  if (auto_generate_food() == ERROR || auto_generate_rocks() == ERROR)
    return (print_error("ERROR Food & Rocks Generation.", 0));
  return (monitor_environment());
}

int				start_listening(int port)
{
  t_sockaddr			addr;
  int				fd;

  if ((fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1)
    return (print_error("ERROR [socket] :", 1));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  addr.sin_addr.s_addr = INADDR_ANY;
  if (bind(fd, (const struct sockaddr *)(&addr), sizeof(addr)) == -1)
    return (print_error("ERROR [bind] :", 1));
  if (listen(fd, SOMAXCONN) == -1)
    return (print_error("ERROR [listen] :", 1));
  return (fd);
}

int				clean_everything(void)
{
  team_destroy();
  socket_destroy();
  board_destroy();
  rocks_destroy();
  food_destroy();
  log_file_destroy();
  return (OK);
}
