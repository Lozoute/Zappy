/*
** server.h for Zappy in /home/lks/rendu/PSU_2014_zappy/server
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Tue Jun 16 16:02:05 2015 Thibaud Auzou
** Last update Sun Jul  5 23:14:52 2015 Thibaud Auzou
*/

#ifndef SERVER_H_
# define SERVER_H_

# include "zappy.h"

/*
** Usage (The Norm Is Like Super Silly Here...)
*/
# define USAGE_S_1	"Usage : ./zappy_server [-p port] [-x size_x] "
# define USAGE_S_2	"[-y size_y] [-c max_client] [-t speed] "
# define USAGE_S_4	"[--debug=[full, sys, teams, board]] "
# define USAGE_S_3	"-n team_name_1 team_name_2 ..."
# define USAGE_SERVER	USAGE_S_1 USAGE_S_2 USAGE_S_4 USAGE_S_3

/*
** Misc
*/
# define BUFF_SIZE	512
# define LOG_FILE	"trace.log"
# define MAX_ERROR	42
# define SEP		"\n"
# define CMD_SEP	" "
# define NB_ROCKS	6
# define RDM_TOLERANCE	7
# define ROCK_RATIO	1
# define FOOD_RATIO	1
# define PV_RATIO	126
# define NB_IA_CMD	12
# define NB_GRAPHIC_CMD	9
# define KO		"ko\n"
# define ROK		"ok\n"
# define MAX_EXEC	10
# define NB_BAG		7
# define RBAD		"sbp\n"
# define RNOT		"suc\n"
# define _F		__FILE__
# define _L		__LINE__
# define USEC		1000000
# define FUSEC		1000000.0
# define LLU		long long unsigned int

/*
** Parameters, Definitions,  Min & Max
*/
# define NB_PARAM	4
# define NB_CHECK_PARAM	7
# define PARAMS_STR	"-p", "-x", "-y", "-c", "-t", "--debug=", "-n"

# define MAX_X		100
# define MAX_Y		100
# define MAX_C		100
# define MAX_T		200
# define MAX_N		10

# define MIN_X		5
# define MIN_Y		5
# define MIN_C		1
# define MIN_T		1
# define MIN_N		2

# define DEFAULT_D	0
# define DEFAULT_P	4242
# define DEFAULT_X	15
# define DEFAULT_Y	15
# define DEFAULT_C	6
# define DEFAULT_T	100
# define DEBUG_SYS	0x000000FF
# define DEBUG_TEAM	0x0000FF00
# define DEBUG_BOARD	0x00FF0000

/*
** Actions Types For Wrappers C+
*/
typedef enum		e_wrap_action
  {
    GET,
    SET,
    CLEAN,
    DESTROY,
  }			t_wrap_action;

/*
** Socket Types By Purpose
*/
typedef enum		e_socket_type
  {
    SERVER,
    CLIENT,
  }			t_socket_type;

/*
** Generic List
*/
typedef int		(*t_del_func) (void *);
typedef int		(*t_cmp_func) (void *, void *);

typedef struct		s_list
{
  void			*_elem;
  struct s_list		*_next;
  struct s_list		*_prev;
}			t_list;

/*
** Application
*/
typedef struct		s_socket t_socket;
typedef struct		s_team t_team;
typedef int		(*t_entry_point_func)(t_socket *, char *);

typedef enum		e_direction
  {
    TOP			= 0,
    RIGHT		= 1,
    BOTTOM		= 2,
    LEFT		= 3,
  }			t_direction;

typedef enum		e_app_type
  {
    UNKNOWN,
    IA,
    GRAPHIC,
  }			t_app_type;

typedef struct		s_application
{
  int			_connected;
  t_app_type		_type;
  t_entry_point_func	_entry_point;
  t_team		*_team;
  int			_x;
  int			_y;
  t_direction		_direction;
  int			_pv;
  int			_lvl;
  t_list		*_exec;
  int			_nb_exec;
  int			_bag[NB_BAG];
}			t_application;

/*
** Buffer Structure
*/
typedef struct		s_buffer
{
  char			_read_buff[BUFF_SIZE * 2];
  int			_read_pos;
  t_list		*_msg;
  char			_args_buff[BUFF_SIZE];
}			t_buffer;

/*
** Why Not ?
*/
typedef struct		s_team t_team;
typedef struct		sockaddr_in t_sockaddr;
typedef struct		timeval t_timeval;
typedef struct		s_socket t_socket;
typedef int		(*t_check_param_func) ();
typedef int		(*t_read_func) (t_socket *);
typedef int		(*t_write_func) (t_socket *);

/*
** Socket Structure / Client
*/
typedef struct		s_socket
{
  int			_fd;
  int			_blocked;
  t_socket_type		_socket_type;
  t_buffer		_buff;
  t_read_func		_read_func;
  t_write_func		_write_func;
  t_application		_application;
}			t_socket;

/*
** Egg Structure
*/
typedef struct		s_egg
{
  int			_ready;
  int			_delay;
  int			_x;
  int			_y;
  int			_pv;
  int			_id;
  int			_dad;
}			t_egg;

/*
** Team Structure
*/
typedef struct		s_team
{
  int			_id;
  char			_name[BUFF_SIZE];
  t_list		*_members;
  t_list		*_eggs;
  t_list		*_ceggs;
  int			_nb_members;
  int			_slots;
}			t_team;

/*
** Items
*/
typedef enum		e_item_type
  {
    PLAYER,
    EGG,
    ROCK,
    FOOD,
  }			t_item_type;

typedef	struct		s_item
{
  t_item_type		_type;
  void			*_item;
}			t_item;

/*
** Rocks
*/
typedef enum		e_rock_type
{
  LINEMATE		= 0,
  DERAUMERE		= 1,
  SIBUR			= 2,
  MENDIANE		= 3,
  PHIRAS		= 4,
  THYSTAME		= 5,
}			t_rock_type;

typedef struct		s_rock
{
  t_rock_type		_type;
  char			*_name;
}			t_rock;

extern const t_rock	g_rock_str[];

/*
** Commands Structure
*/
typedef int		(*t_cmd_func)(t_socket *);

typedef struct		s_cmd
{
  char			*_name;
  int			_delay;
  t_cmd_func		_func;
}			t_cmd;

typedef struct		s_exec
{
  int			_delay;
  t_cmd_func		_func;
  char			_args[BUFF_SIZE];
}			t_exec;

/*
** Elevation Conditions Structure
*/
# define NB_LVL		7

extern int		g_elevation[NB_LVL][NB_LVL];

/*
** Initialization (server.c)
*/
int			start_server(void);
int			start_listening(int);
int			clean_everything(void);
void			ctrl_c(int);

/*
** Signals (signals/ *.c)
*/
int			signals_init(void);
void			sigint(int);

/*
** Monitoring Environment (monitoring/ *.c)
*/
int			monitor_environment(void);
void			choose_fd(int *, fd_set *, fd_set *);
void			do_read_and_write(fd_set *, fd_set *);
int			do_read(t_socket *, fd_set *);
int			do_write(t_socket *, fd_set *);

/*
** Server States (states/ *.c)
*/
void			shutdown_server(void);
int			server_running(void);

/*
** Error Module, Printing And Loging (error/ *.c)
*/
int			print_error(const char *, int);
int			print_warning(const char *);
int			log_err(const char *, int, int, ...);
void			add_global_error(void);
FILE			*log_file_init(void);
FILE			*get_log_file(void);
void			log_file_destroy(void);
int			log_evt(const char *, ...);
int			log_nok(const char *, ...);

/*
** Parameters Checking, Storing And Retreiving (parameters/ *.c)
*/
int			check_parameters(int, char **);
int			check_param_p(char *);
int			check_param_x(char *);
int			check_param_y(char *);
int			check_param_c(char *);
int			check_param_t(char *);
int			check_param_n(char **);
int			check_param_d(char *);
int			get_port(void);
void			set_port(int);
void			set_time(int);
int			get_time(void);
int			get_number_client(void);
void			set_number_client(int);
int			check_param_c(char *);
int			get_size_y(void);
void			set_size_y(int);
int			get_size_x(void);
void			set_size_x(int);
int			check_param_y(char *);
int			is_debug(void);
void			set_debug(int);

/*
** Generic List Module (list/ *.c)
*/
int			add_to_list_end(t_list **, void *);
int			add_to_list_begin(t_list **, void *);
int			rm_from_list(t_list **,
				     void *,
				     t_cmp_func,
				     t_del_func);
void			*find_in_list(t_list **, void*, t_cmp_func);
int			destroy_list(t_list **, t_del_func);
void			list_pop_head(t_list **, t_del_func);
void			*list_pop(t_list **, void *, t_cmp_func);

/*
** Socket Environment (socket/ *.c)
*/
t_socket		*create_socket(t_socket_type, int);
int			remove_socket(t_socket *);
t_list			**get_list_socket(void);
int			socket_server_init(t_socket *);
int			socket_server_read_func(t_socket *);
int			socket_client_init(t_socket *);
int			socket_client_read_func(t_socket *);
int			socket_client_write_func(t_socket *);
int			socket_cmp_func_by_fd(void *, void *);
int			socket_cmp_func_by_fd_only(void *, void *);
int			socket_cmp_func_by_ptr(void *, void *);
int			socket_del_func(void *);
int			socket_client_disconnect(t_socket *);
int			socket_destroy(void);
t_socket		*get_socket(int);

/*
** Teams (teams/ *.c)
*/
t_team			*create_team(int, char *);
int			remove_team(t_team *);
t_list			**get_list_teams(void);
t_team			*find_team(char *);
int			team_cmp_func_by_name(void *, void *);
int			team_cmp_func_by_name_and_team(void *, void *);
int			team_del_func(void *);
int			team_destroy(void);
int			add_player_to_team(t_team *, t_socket *);
int			remove_player_from_team(t_team *, t_socket *);
int			cook_eggs(t_team *);
int			team_cmp_egg_by_ptr(void *, void *);
int			team_del_egg_func(void *);
int			fry_eggs(t_team *);

/*
** Buffers (buffer/ *.c)
*/
void			buffer_init(t_buffer *);
void			buffer_copy(t_buffer *, char *);
void			buffer_str_copy(char *, char *, int);
char			*buffer_split(t_buffer *, char *);
int			add_msg_to_buffer(t_buffer *, char *);
int			add_msg_to_buffer_nodup(t_buffer *, char *);
int			buffer_del_func(void *);

/*
** Application Layer Overall (application/ *.c)
*/
int			application_init(t_application *);
int			application_treat_data(t_socket *, char *);
int			application_try_to_connect(t_socket *, char *);
int			application_graphic_init(t_socket *);
int			application_ia_init(t_socket *, t_team *);
int			take_egg(t_socket *, t_team *);
int			entry_point_ia(t_socket *, char *);
int			entry_point_graphic(t_socket *, char *);
int			application_exec_cycle(t_socket *);
int			add_cmd_to_queue(t_socket *, int, t_cmd_func, int);
int			exec_del_func(void *);
int			check_incant(t_socket *);

/*
** Cycle (cycle/ *.c)
*/
t_timeval		*get_cycle(void);
size_t			get_cycle_number(t_wrap_action);
size_t			get_average_cycle(t_wrap_action, size_t);
size_t			get_ucycle(void);
size_t			cycle_diff(t_timeval *, t_timeval *);
int			cycle_need_to_be_executed(void);
int			cycle_execute(t_wrap_action, int);
size_t			cycle_delta(t_wrap_action, size_t);
int			first_cycle(t_wrap_action);

/*
** Board Manipulation (board/ *.c)
*/
t_list			**get_board(void);
void			board_destroy(void);
int			board_init(void);
t_list			**board_get_at_coord(int, int);
int			board_add_at_coord(int, int, t_item_type, void *);
int			board_add_at_random_coord(t_item_type, void *);
void			board_generate_random_coord(int *, int *, int);
int			board_del_func(void *);
int			board_cmp_func_by_ptr(void *, void *);
int			board_cmp_func_by_type(void *, void *);
int			board_rm_at_coord(int, int, void *);
int			board_cmp_func_by_item(void *, void *);
int			application_exec_cycle_eggs(void);

/*
** Rocks Generation, Removing, etc (rocks/ *.c)
*/
t_list			**get_list_rocks(void);
t_rock			*rocks_generate(void);
void			rocks_delete(t_rock *);
t_rock_type		rocks_get_needed_type(void);
void			rocks_count_incr(t_rock_type);
void			rocks_count_decr(t_rock_type);
int			rocks_cmp_func_by_ptr(void *, void *);
int			rocks_cmp_type_only(void *, void *);
int			rocks_del_func(void *);
void			rocks_destroy(void);
int			auto_generate_rocks(void);
t_rock			*rocks_generate_type(t_rock_type);

/*
** Food Generation, Removing, etc (Food/ *.c)
*/
t_list			**get_list_food(void);
void			food_destroy(void);
int			generate_food(void);
void			food_delete(void);
void			food_count_incr(void);
void			food_count_decr(void);
int			get_food_count(void);
int			auto_generate_food(void);
int			rocks_get_count(t_rock_type);

/*
** Graphic (graphic/ *.c)
*/
t_team			*get_graphic_team(void);
void			set_graphic_team(t_team *);
int			send_msg_graph(char *, ...);

/*
** IA Commands (cmds_ia/ *.c)
*/
int			cmd_ia_avance(t_socket *);
void			cmd_ia_avance_update_coord(int *, int *, t_direction);
int			cmd_ia_droite(t_socket *);
int			cmd_ia_gauche(t_socket *);
int			cmd_ia_voir(t_socket *);
int			cmd_ia_voir_line(t_application *,
					 char **,
					 int *,
					 int);
int			cmd_ia_voir_case(char **, int *, int, int);
int			cmd_ia_voir_type(char **, int *, t_item *);
int			cmd_ia_voir_strcat(char **, int *, char *);
int			cmd_ia_inventaire(t_socket *);
int			cmd_ia_prend(t_socket *);
int			cmd_ia_prend_find_item_type(char *,
						    t_item_type *,
						    t_rock_type *);
int			cmd_ia_prend_pop_item(t_socket *,
					      t_item_type,
					      t_rock_type);
int			cmd_ia_prend_pop_rock(t_socket *, t_rock *);
int			cmd_ia_prend_pop_food(t_socket *,
					      t_list **,
					      t_item *);
int			cmd_ia_pose(t_socket *);
int			cmd_ia_pose_item(t_socket *,
					 t_item_type,
					 t_rock_type);
int			cmd_ia_pose_food(t_socket *);
int			cmd_ia_pose_rock(t_socket *, t_rock_type);
int			cmd_ia_expulse(t_socket *);
int			cmd_ia_expulse_player(t_socket *,
					int *,
					t_direction);
int			cmd_ia_broadcast(t_socket *);
int			cmd_ia_broadcast_to_team(char *,
						 t_team *,
						 t_socket *);
int			cmd_ia_broadcast_calc(t_application *,
					      t_application *);
int			cmd_ia_connect_nbr(t_socket *);
int			cmd_ia_fork(t_socket *);
int			cmd_ia_incantation(t_socket *);
int			cmd_ia_incantation_check_conditions(t_socket *, char *);
int			cmd_ia_incantation_check_case(t_list *, int, char *);
int			cmd_ia_incantation_raise(t_socket *, int);
int			cmd_ia_incantation_raise_player(t_socket *, int);
int			cmd_ia_incantation_raise_rock(int, int, t_rock *, int);
int			cmd_ia_broadcast_min_abs(int, int);
int			cmd_ia_broadcast_dist(int, int, int);
int			cmd_ia_broadcast_relative(int, t_application *);
int			cmd_ia_death(t_socket *);
int			cmd_ia_victory(t_team *);
int			cmd_ia_victory_yes(char *);

/*
** Graphic Commands (cmds_graphic/ *.c)
*/
int			cmd_graphic_welcome(t_socket *);
int			cmd_graphic_welcome_cases(t_socket *);
int			cmd_graphic_welcome_case_count(t_list *, int *);
int			cmd_graphic_welcome_teams(t_socket *);
int			cmd_graphic_welcome_players(t_socket *);
int			cmd_graphic_welcome_eggs(t_socket *);
int			cmd_graphic_welcome_ceggs(t_socket *, t_team *);
int			cmd_graphic_welcome_reggs(t_socket *, t_team *);
int			cmd_graphic_msz(t_socket *);
int			cmd_graphic_bct(t_socket *);
int			cmd_graphic_bct_case(t_socket *, int, int);
int			cmd_graphic_mct(t_socket *);
int			cmd_graphic_tna(t_socket *);
int			cmd_graphic_ppo(t_socket *);
int			cmd_graphic_plv(t_socket *);
int			cmd_graphic_pin(t_socket *);
int			cmd_graphic_pin_player(t_socket *, t_socket *);
int			cmd_graphic_sgt(t_socket *);
int			cmd_graphic_sst(t_socket *);
int			cmd_graphic_prend(t_socket *, int);
int			cmd_graphic_pose(t_socket *, int);
int			cmd_graphic_bct_case_everyone(int, int);

/*
** DEBUG
*/
void			print_debug(void);
void			dump_client(t_socket *);
void			dump_teams(void);
void			dump_team(t_team *);
void			dump_system(void);
void			dump_board(void);

#endif /* !SERVER_H_ */
