/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 08:55:36 by tguillem          #+#    #+#             */
/*   Updated: 2016/11/16 09:00:25 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static t_path	*compute_paths_size(t_path *paths)
{
	t_path		*tmp;

	tmp = paths;
	while (tmp)
	{
		tmp->size = ft_count_char(tmp->path, '-');
		tmp = tmp->next;
	}
	return (paths);
}

static void		set_new(t_path **start, t_path **prev, t_path **new)
{
	if (!*start)
	{
		*prev = *new;
		*start = *prev;
	}
	else
	{
		(*prev)->next = *new;
		(*prev) = (*prev)->next;
	}
}

static void		reset_connections(t_graph *graph, int *bol)
{
	int				i;
	t_connections	*start_connections;

	start_connections = graph->connections;
	i = 0;
	*bol = 0;
	while (graph->connections)
	{
		if (!graph->connections->link->ran && !graph->connections->link->end)
			*bol = 1;
		if (graph->connections->link->weight == graph->weight - 1
				&& graph->connections->link->ran == 0)
			i = 1;
		graph->connections = graph->connections->next;
	}
	if (i == 0)
		graph->weight++;
	graph->connections = start_connections;
}

static t_path	*compute_paths(t_graph *graph)
{
	t_path	*prev;
	t_path	*start;
	t_path	*new;
	int		bol;

	bol = 1;
	start = NULL;
	while (!graph->begin)
		graph = graph->next;
	while (bol == 1 && graph->weight != -1)
	{
		if ((new = get_path(graph)))
			set_new(&start, &prev, &new);
		else
			reset_connections(graph, &bol);
	}
	return (start);
}

void			start_resolver(t_data *data)
{
	t_path		*paths;
	t_path		*move;

	move = NULL;
	paths = compute_paths(data->graph);
	paths = compute_paths_size(paths);
	if (paths->size == 1)
		return (display_one_path(paths, data->ant_count));
	while (data->ant_count > 0 || move)
		move = move_ant(data, paths, move);
}
