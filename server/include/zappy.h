/*
** zappy.h for Zappy in /home/auzou_t/rendu/PSU_2014_zappy
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Mon Jun 15 17:44:09 2015 Thibaud Auzou
** Last update Thu Jun 25 02:03:53 2015 Thibaud Auzou
*/

#ifndef ZAPPY_H_
# define ZAPPY_H_

/*
** LibC
*/
# include <unistd.h>
# include <string.h>
# include <strings.h>
# include <stdlib.h>
# include <errno.h>
# include <stdio.h>
# include <signal.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <time.h>
# include <ctype.h>
# include <dirent.h>
# include <stdarg.h>
# include <sys/types.h>
# include <sys/ioctl.h>
# include <sys/time.h>
# include <limits.h>

/*
** Network - TCP/IP
*/
# include <sys/socket.h>
# include <netdb.h>
# include <netinet/in.h>
# include <netinet/ip.h>
# include <netinet/tcp.h>
# include <arpa/inet.h>

/*
** Return Codes
*/
# define ERROR			-1
# define OK			1
# define NOK			0

#endif /* !ZAPPY_H_ */
