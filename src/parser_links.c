#include "lemin.h"

static void	link_graph_one(t_graph *tmp1, t_graph *tmp2)
{
	t_connections	*new;
	t_connections	*run;

	if (!(new = (t_connections*) ft_memalloc(sizeof(t_connections))))
		return ;
	new->next = NULL;
	new->link = tmp2;
	if (!tmp1->connections)
	{
		tmp1->connections = new;
		return ;
	}
	run = tmp1->connections;
	while (run->next)
		run = run->next;
	run->next = new;
}

static void	link_graph(char *line, t_graph **graph)
{
	char	*id1;
	char	*id2;
	t_graph	*tmp1;
	t_graph	*tmp2;
	t_graph	*run;

	run = *graph;
	id1 = line;
	id2 = ft_strchr(line, '-');
	*id2 = '\0';
	id2++;
	while (run)
	{
		if (ft_strcmp(run->id, id1) == 0)
			tmp1 = run;
		if (ft_strcmp(run->id, id2) == 0)
			tmp2 = run;
		run = run->next;
	}
	link_graph_one(tmp1, tmp2);
	link_graph_one(tmp2, tmp1);
	id2--;
	*id2 = '-';
}

int			compute_connections(t_array **map, t_graph **graph)
{
	int		add;

	while (*map)
	{
		while (is_excluded_command((*map)->data))
		{
			*map = (*map)->next;
			if (!*map)
				return (-1);
		}
		if ((add = is_valid_room_link((*map)->data, *graph)) == -1)
			return (-1);
		else if (add == 1)
			link_graph((*map)->data, graph);
		*map = (*map)->next;
	}
	return (-1);
}
