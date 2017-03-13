/*
** log_error.c for Zappy in /home/lks/rendu/PSU_2014_zappy/server
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Tue Jun 16 22:04:12 2015 Thibaud Auzou
** Last update Fri Jul  3 14:14:17 2015 Thibaud Auzou
*/

#include "server.h"

static int	global_error(t_wrap_action action)
{
  static int	_errors = 0;

  if (action == SET)
    _errors++;
  else if (action == CLEAN)
    _errors = 0;
  return (_errors);
}

int		log_err(const char *msg, int err, int global, ...)
{
  extern int	errno;
  char		b[BUFF_SIZE * 2];
  char		a[BUFF_SIZE];
  FILE		*file;
  va_list	va;
  time_t	t;
  char		*date;

  if (msg == NULL || (file = get_log_file()) == NULL)
    return (ERROR);
  va_start(va, global);
  if (time(&t) == -1)
    return (ERROR);
  if ((date = ctime(&t)) == NULL)
    return (ERROR);
  date[strlen(date) - 1] = 0;
  vsprintf(a, msg, va);
  sprintf(b, "[%s] %s%s\n", date, a, (err ? strerror(errno) : ""));
  fputs(b, file);
  va_end(va);
  if (global)
    add_global_error();
  return (ERROR);
}

void		add_global_error(void)
{
  if (global_error(SET) > MAX_ERROR)
    shutdown_server();
}

int		log_evt(const char *msg, ...)
{
  char		b[BUFF_SIZE * 2];
  char		a[BUFF_SIZE];
  FILE		*file;
  va_list	va;
  time_t	t;
  char		*date;

  if (msg == NULL || (file = get_log_file()) == NULL)
    return (ERROR);
  va_start(va, msg);
  vsprintf(a, msg, va);
  if (time(&t) == -1)
    return (ERROR);
  if ((date = ctime(&t)) == NULL)
    return (ERROR);
  date[strlen(date) - 1] = 0;
  sprintf(b, "[%s] %s\n", date, a);
  fputs(b, file);
  va_end(va);
  return (OK);
}

int		log_nok(const char *msg, ...)
{
  char		b[BUFF_SIZE * 2];
  char		a[BUFF_SIZE];
  FILE		*file;
  va_list	va;
  time_t	t;
  char		*date;

  if (msg == NULL || (file = get_log_file()) == NULL)
    return (ERROR);
  va_start(va, msg);
  vsprintf(a, msg, va);
  if (time(&t) == -1)
    return (ERROR);
  if ((date = ctime(&t)) == NULL)
    return (ERROR);
  date[strlen(date) - 1] = 0;
  sprintf(b, "[%s] %s\n", date, a);
  fputs(b, file);
  va_end(va);
  return (NOK);
}
