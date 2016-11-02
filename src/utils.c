#include "lemin.h"

int				is_room_id_availaible(char *line, t_graph *graph)
{
	char	*tmp;

	tmp = ft_strchr(line, ' ');
	*tmp = '\0';
	while (graph)
	{
		if (ft_strcmp(line, graph->id) == 0)
		{
			*tmp = ' ';
			return (-1);
		}
		graph = graph->next;
	}
	*tmp = ' ';
	return (1);
}

int				is_excluded_command(char *line)
{
	return (ft_strncmp(line, "#", 1) == 0 && ft_strncmp(line, "##start\0", 8)
		!= 0 && ft_strncmp(line, "##end\0", 6) != 0);
}

int				is_room_link(char *line)
{
	char	**line_split;
	int		i;

	if (line[0] == '#')
		return (0);
	line_split = ft_strsplit(line, '-');
	i = 0;
	while (line_split[i])
	{
		free(line_split[i]);
		i++;
	}
	if (i != 2)
		return (0);
	return (1);
}

int				is_valid_identifier(char *line, t_graph *graph)
{
	int		i;
	int		ret;

	ret = 0;
	i = 0;
	if (line[0] == 'L')
		return (0);
	while (line[i] && line[i] != ' ')
	{
		if (line[i] == '-')
			return (0);
		i++;
	}
	if (i != 0)
		ret = validate_block(line, &i);
	if (ret == 1)
		ret = validate_block(line, &i);
	if (ret == 1 && !line[i])
		return (is_room_id_availaible(line, graph));
	return (0);
}

int		is_connection_availaible(t_graph *first, t_graph *sec)
{
	t_connections	*tmp;

	tmp = first->connections;
	while (tmp)
	{
		if (ft_strcmp(tmp->link->id, sec->id) == 0)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}
