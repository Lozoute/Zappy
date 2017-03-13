/*
** socket.h for zappy in /home/helleg_f/rendu/PSU_2014_zappy/ai/c_socket
** 
** Made by florian hellegouarch
** Login   <helleg_f@epitech.net>
** 
** Started on  Wed Jun 17 16:20:21 2015 florian hellegouarch
** Last update Sun Jul  5 03:23:11 2015 florian hellegouarch
*/

#ifndef PROTOCOL_H_
# define PROTOCOL_H_

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/socket.h>
# include <netdb.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <arpa/inet.h>
# include <errno.h>

# define BUFF_SIZE	4096
# define ERROR_COLOR	"\e[1;31m"
# define OK_COLOR	"\e[1;34m"
# define HELP_COLOR	"\e[1;32m"
# define RESET_COLOR	"\e[0m"
# define CONNECT_ERR	"couldn't connect to server"
# define PROTO_ERR	"couldn't get protocol TCP"
# define INIT_ERR	"couldn't init socket"
# define SOCKET_CL_ERR	"failed to close socket"
# define RD_ERR		"failed to read"
# define WR_ERR		"failed to write"
# define MALLOC_ERR	"failed to malloc"

int			socket_init_clt(char const *ip, char const *port);
int			close_socket(int fd);
void			perror_color(char const *error);
char			get_char(int fd);
int			write_line(int fd, const char *str);

#endif /* !PROTOCOL_H_ */
