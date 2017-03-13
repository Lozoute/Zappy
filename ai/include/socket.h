/*
** socket.h for zappy in /home/helleg_f/rendu/PSU_2014_zappy/ai/include
** 
** Made by florian hellegouarch
** Login   <helleg_f@epitech.net>
** 
** Started on  Wed Jun 17 16:20:21 2015 florian hellegouarch
** Last update Sun Jul  5 03:20:10 2015 florian hellegouarch
*/

#ifndef PROTOCOL_H_
# define PROTOCOL_H_

extern "C"
{
  int			socket_init_clt(char const *ip, char const *port);
  int			close_socket(int fd);
  void			perror_color(char const *error);
  int			get_char(int fd);
  int			write_line(int fd, const char *str);
}

#endif /* !PROTOCOL_H_ */
