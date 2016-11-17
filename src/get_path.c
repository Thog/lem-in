/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 08:56:10 by tguillem          #+#    #+#             */
/*   Updated: 2016/11/17 15:06:18 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static char		*compute_response_name(char *way, char *add)
{
	if (!way)
		return (ft_strdup(add));
	way = ft_strfjoin(way, "-");
	way = ft_strfjoin(way, add);
	return (way);
}

static t_path	*compute_path_response(t_graph *graph, char *way, t_path *new)
{
	if (!graph->end)
	{
		free(way);
		free(new);
		return (NULL);
	}
	way = compute_response_name(way, graph->id);
	if (ft_count_char(way, '-') == 1)
		graph->weight--;
	new->next = NULL;
	new->path = way;
	return (new);
}

t_path			*get_path(t_graph *graph)
{
	t_path			*new;
	t_connections	*connections;
	char			*way;

	way = NULL;
	new = ft_memalloc(sizeof(t_path));
	connections = graph->connections;
	while (connections && !graph->end)
	{
		if (connections->link->weight == graph->weight - 1 &&
				!connections->link->ran)
		{
			way = compute_response_name(way, graph->id);
			graph = connections->link;
			if (!graph->end)
				graph->ran = 1;
			connections = graph->connections;
		}
		else
			connections = connections->next;
	}
	return (compute_path_response(graph, way, new));
}
