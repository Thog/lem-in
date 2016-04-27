/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/27 12:17:24 by tguillem          #+#    #+#             */
/*   Updated: 2016/04/27 17:21:50 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_data			*init_data(void)
{
	t_data		*data;

	if (!(data = ft_memalloc(sizeof(t_data))))
		return (NULL);
	return (data);
}

void			destroy_data(t_data **data)
{
	if (data)
		ft_memdel((void **)data);
}

t_nodelst		*init_nodelst(t_nodelst *root, t_node *data)
{
	t_nodelst		*result;
	t_nodelst		*tmp;

	tmp = root;
	if (!(result = (t_nodelst*)ft_memalloc(sizeof(t_nodelst))))
		return (NULL);
	result->data = data;
	result->next = NULL;
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = result;
		return (root);
	}
	return (result);
}

t_connection	*init_connection(t_connection *root, char *room_one,
	char *room_two)
{
	t_connection	*result;
	t_connection	*tmp;

	tmp = root;
	if (!(result = (t_connection*)ft_memalloc(sizeof(t_connection))))
		return (NULL);
	result->room_one = room_one;
	result->room_two = room_two;
	result->next = NULL;
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = result;
		return (root);
	}
	return (result);
}

t_node			*new_node(char *identifier, int x, int y)
{
	t_node	*ret;

	if (!(ret = ft_memalloc(sizeof(t_node))))
		return (NULL);
	ret->identifier = identifier;
	ret->x = x;
	ret->y = y;
	return (ret);
}
