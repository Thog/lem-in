#include "lemin.h"

int		is_valid_room_link(char *line, t_graph *graph)
{
	char	**link_split;
	int		i;
	t_graph	*tmp1;
	t_graph	*tmp2;

	i = 0;
	tmp1 = NULL;
	tmp2 = NULL;
	link_split = ft_strsplit(line, '-');
	while (link_split[i])
		i++;
	if (i != 2 || ft_strcmp(link_split[0], link_split[1]) == 0)
		return (0);
	while (graph)
	{
		if (ft_strcmp(link_split[0], graph->id) == 0)
			tmp1 = graph;
		if (ft_strcmp(link_split[1], graph->id) == 0)
			tmp2 = graph;
		graph = graph->next;
	}
	if (tmp1 && tmp2)
		return (is_connection_availaible(tmp1, tmp2));
	return (-1);
}
