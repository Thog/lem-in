/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroyer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 10:13:27 by tguillem          #+#    #+#             */
/*   Updated: 2016/11/16 10:20:11 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	destroy_connections(t_connections *connections)
{
	t_connections *tmp;
	t_connections *prev;

	tmp = connections;
	prev = NULL;
	while (tmp)
	{
		ft_memdel((void**)&prev);
		prev = tmp;
		tmp = tmp->next;
	}
	ft_memdel((void**)&prev);
}

void	destroy_graph(t_graph *graph)
{
	t_graph *tmp;
	t_graph *prev;

	tmp = graph;
	prev = NULL;
	while (tmp)
	{
		destroy_connections(tmp->connections);
		ft_strdel(&tmp->id);
		ft_memdel((void**)&prev);
		prev = tmp;
		tmp = tmp->next;
	}
	ft_memdel((void**)&prev);
}

void	destroy_split(char **line_split)
{
	int i;

	i = 0;
	while (line_split[i])
	{
		ft_strdel((line_split + i));
		i++;
	}
	ft_memdel((void**)&line_split);
}

int		destroy_split_ret(char **line_split, int code)
{
	destroy_split(line_split);
	return (code);
}
