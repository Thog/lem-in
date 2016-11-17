/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 08:57:12 by tguillem          #+#    #+#             */
/*   Updated: 2016/11/16 09:09:14 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int				validate_block(char *line, int *state)
{
	int			nb_exist;

	if (line[*state] == ' ')
	{
		(*state)++;
		while (line[*state] && ft_isdigit(line[*state]))
		{
			(*state)++;
			nb_exist = 1;
		}
		if (nb_exist == 1)
			return (1);
	}
	return (0);
}

int				is_valid_room_link(char *line, t_graph *graph)
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
		return (destroy_split_ret(link_split, 0));
	while (graph)
	{
		if (ft_strcmp(link_split[0], graph->id) == 0)
			tmp1 = graph;
		if (ft_strcmp(link_split[1], graph->id) == 0)
			tmp2 = graph;
		graph = graph->next;
	}
	destroy_split(link_split);
	if (tmp1 && tmp2)
		return (is_connection_availaible(tmp1, tmp2));
	return (-1);
}

static void		compute_weights(t_graph *graph, int weight, int *begin)
{
	t_connections	*connections;

	connections = NULL;
	if (*begin == 0 && graph->begin)
		*begin = 1;
	if (graph->weight > weight)
		graph->weight = weight;
	if (graph->connections)
		connections = graph->connections;
	while (connections)
	{
		if (weight < connections->link->weight)
			compute_weights(connections->link, weight + 1, begin);
		connections = connections->next;
	}
}

int				is_valid(t_graph *graph)
{
	t_graph	*end;
	t_graph	*tmp;
	int		begin;

	begin = 0;
	end = NULL;
	tmp = graph;
	while (tmp)
	{
		if (tmp->begin)
			begin = 1;
		if (tmp->end)
			end = tmp;
		tmp = tmp->next;
	}
	if (begin == 1 && end)
	{
		begin = 0;
		compute_weights(end, 0, &begin);
		if (begin == 1)
			return (1);
	}
	return (0);
}
