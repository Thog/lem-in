#include "lemin.h"

static int		is_command(char *data)
{
	static int	start_defined = 0;
	static int	end_defined = 0;

	if (ft_strncmp(data, "##start\0", 8) == 0)
	{
		if (start_defined == 1)
			return (-1);
		start_defined = 1;
		return (1);
	}
	else if (ft_strncmp(data, "##end\0", 6) == 0)
	{
		if (end_defined == 1)
			return (-1);
		end_defined = 1;
		return (2);
	}
	return (0);
}

int				check_command(t_array **map, t_graph **graph)
{
	int		cmd;

	if ((cmd = is_command((*map)->data)) == -1 || cmd == 0)
		return (cmd);
	if ((*map)->next && (*map)->next->data)
		*map = (*map)->next;
	while (is_excluded_command((*map)->data) && (*map)->next && (*map)->next->data)
		(*map) = (*map)->next;
	if (!is_valid_identifier((*map)->data, *graph))
		return (-1);
	*graph = init_new_graph(*graph, (*map)->data, cmd);
	return (1);
}

static t_graph	*parse_graph(t_array *map)
{
	t_graph	*graph;
	int		code;

	code = 1;
	graph = NULL;
	while (map && map->data && code == 1)
	{
		code = is_excluded_command(map->data);
		if (!code && is_room_link(map->data))
			code = compute_connections(&map, &graph);
		else if (!code && (code = is_valid_identifier(map->data, graph)) == 1)
			graph = init_new_graph(graph, map->data, 0);
		code = (!code ? check_command(&map, &graph) : code);
		if (code != -1)
			map = map->next;
	}
	if (map)
		map->data = NULL;
	return (graph);
}

int				init_data(t_data *data, t_array *map)
{
	int		i;
	int		error;

	i = 0;
	error = 0;
	while (map && map->data && map->data[i])
	{
		if (!ft_isdigit(map->data[i]))
			error = 1;
		i++;
	}
	if (map->data)
		data->ant_count = ft_atoi(map->data);
	data->graph = NULL;
	if (data->ant_count <= 0 || error == 1)
		return (1);
	data->graph = parse_graph(map->next);
	return (0);
}
