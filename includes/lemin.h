#ifndef LEMIN_H
# define LEMIN_H
# include "libft.h"
# include <fcntl.h>
# include <unistd.h>

typedef struct		s_lst
{
	char			*line;
	struct s_lst	*next;
}					t_lst;

typedef struct		s_path
{
	char			*path;
	int				size;
	struct s_path	*next;
}					t_path;

typedef struct				s_connections
{
	struct s_graph			*link;
	struct s_connections	*next;
}							t_connections;

typedef struct		s_graph
{
	char			*id;
	t_connections	*connections;
	int				x;
	int				y;
	int				weight;
	int				ran;
	unsigned char	begin;
	unsigned char	end;
	struct s_graph	*next;
}					t_graph;

typedef struct		s_data
{
	int				ant_count;
	t_graph			*graph;
}					t_data;

void 		store_map(t_array **data);
int			is_excluded_command(char *line);
int			is_room_link(char *line);
int			validate_block(char *line, int *state);
int			is_valid_room_link(char *line, t_graph *graph);
int			is_valid_identifier(char *line, t_graph *graph);
int			is_room_id_availaible(char *line, t_graph *graph);
int			init_data(t_data *data, t_array *map);
int			compute_connections(t_array **map, t_graph **graph);
int			check_command(t_array **map, t_graph **graph);
int			is_connection_availaible(t_graph *first, t_graph *sec);
t_graph		*init_new_graph(t_graph *graph, char *data, int i);
t_path		*get_path(t_graph *graph);
int			ft_count_char(char *str, char c);
char		*ft_strfjoin(char const *s1, char const *s2);
void		display_one_path(t_path *path, int ant);
void		start_resolver(t_data *data);
t_path		*move_ant(t_data *data, t_path *paths, t_path *move);
t_path		*get_next_move(t_data *data, char *path, t_path *move);
int			is_valid(t_graph *graph);
#endif
