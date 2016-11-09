#include "lemin.h"

static t_graph		*search_graph(char *data, t_graph *graph)
{
	data = ft_strchr(data, ' ');
	*data = '\0';
	while (graph)
	{
		if (ft_strcmp(data, graph->id) == 0)
		{
			*data = ' ';
			return (graph);
		}
		graph = graph->next;
	}
	*data = ' ';
	return (NULL);
}

static t_graph		*init_grah(char *data, int cmd)
{
	t_graph	*graph;
	char	**data_split;

	if (!(graph = (t_graph *) malloc(sizeof(t_graph))))
		return (NULL);
	data_split = ft_strsplit(data, ' ');
	graph->id = data_split[0];
	graph->x = ft_atoi(data_split[1]);
	graph->y = ft_atoi(data_split[2]);
	graph->weight = 2147483647;
	graph->ran = 0;
	free(data_split[1]);
	free(data_split[2]);
	graph->connections = NULL;
	graph->begin = (cmd == 1 ? '1' : 0);
	graph->end = (cmd == 2 ? '1' : 0);
	graph->next = NULL;
	return (graph);
}

t_graph		*init_new_graph(t_graph *graph, char *data, int cmd)
{
	t_graph	*new;
	t_graph	*tmp;

	tmp = graph;
	if (!graph)
		return (init_grah(data, cmd));
	if (!(new = search_graph(data, graph)))
	{
		new = init_grah(data, cmd);
		new->next = graph;
		return (new);
	}
	graph->begin = (cmd == 1 ? '1' : 0);
	graph->end = (cmd == 2 ? '1' : 0);
	return (tmp);
}
