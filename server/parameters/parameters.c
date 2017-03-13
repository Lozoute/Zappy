/*
** parameters.c for Zappy in /home/lks/rendu/PSU_2014_zappy/server
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Tue Jun 16 18:29:07 2015 Thibaud Auzou
** Last update Sun Jul  5 23:20:56 2015 Thibaud Auzou
*/

#include "server.h"

static void			check_f_init(t_check_param_func *check_f)
{
  check_f[0] = &check_param_p;
  check_f[1] = &check_param_x;
  check_f[2] = &check_param_y;
  check_f[3] = &check_param_c;
  check_f[4] = &check_param_t;
  check_f[5] = &check_param_d;
  check_f[6] = &check_param_n;
}

static int			param_exists(char **params, char *token)
{
  int				i;

  for (i = 0; i < NB_CHECK_PARAM; ++i)
    if (!strcmp(params[i], token) ||
	(i == NB_CHECK_PARAM - 2 &&
	 !strncmp(token, params[i], strlen(params[i]))))
      return (i);
  return (-1);
}

static int			check_param(char **params,
					    char *token,
					    int *done)
{
  char				b[BUFF_SIZE];
  int				p;

  if ((p = param_exists(params, token)) == -1)
    {
      sprintf(b, "Unknown Parameter %s", token);
      return (print_error(b, 0));
    }
  if (done[p])
    {
      sprintf(b, "Double Definition Of Parameter %s", token);
      return (print_error(b, 0));
    }
  return (p);
}

int				check_parameters(int argc, char **argv)
{
  static t_check_param_func	check_f[NB_CHECK_PARAM] = {NULL};
  static char			*params[NB_CHECK_PARAM] = {PARAMS_STR};
  int				done[NB_CHECK_PARAM];
  int				i;
  int				p;

  memset(&done, 0, sizeof(int) * NB_CHECK_PARAM);
  check_f_init(check_f);
  for (i = 1; i < argc; ++i)
    {
      if ((p = check_param(params, argv[i], done)) == ERROR)
	return (ERROR);
      if (p < NB_CHECK_PARAM - 2 && (*check_f[p])(argv[i + 1]) == ERROR)
	return (ERROR);
      else if (p == NB_CHECK_PARAM - 2 && (*check_f[p])(argv[i]) == ERROR)
	return (ERROR);
      else if (p == NB_CHECK_PARAM - 1)
	return ((*check_f[p])(&(argv[i + 1])));
      i = (p < NB_CHECK_PARAM - 2 ? i + 1 : i);
      done[p] = 1;
    }
  if (!done[NB_CHECK_PARAM - 1])
    return (print_error("You Must Secify 2 Teams Minimum", 0));
  return (OK);
}
