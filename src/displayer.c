/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   displayer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 08:56:02 by tguillem          #+#    #+#             */
/*   Updated: 2016/11/16 09:04:42 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void			select_path_next(char **new, t_path **path)
{
	char		*tmp;

	tmp = ft_strchr((*path)->path + 1, '-');
	if (tmp)
	{
		*new = ft_strdup(tmp);
		free((*path)->path);
		(*path)->path = *new;
	}
	else
	{
		free((*path)->path);
		(*path)->path = NULL;
	}
}

static t_path		*select_path(t_path *move)
{
	t_path		*tmp;
	char		*new;
	t_path		*prev;

	tmp = move;
	prev = NULL;
	while (tmp)
	{
		if (tmp->path)
			select_path_next(&new, &tmp);
		prev = tmp;
		tmp = tmp->next;
	}
	return (prev);
}

static void			display_move_next(t_path *path, int *i)
{
	char		*tmp;

	if (*i != 0)
		ft_putchar(' ');
	*i = 1;
	ft_putstr("L");
	ft_putnbr(path->size);
	if ((tmp = ft_strchr(path->path + 1, '-')))
		*tmp = '\0';
	ft_putstr(path->path);
	if (tmp)
		*tmp = '-';
}

static t_path		*display_move(t_path *move)
{
	int			i;
	t_path		*tmp;

	i = 0;
	tmp = move;
	while (tmp)
	{
		if (tmp->path)
			display_move_next(tmp, &i);
		tmp = tmp->next;
	}
	if (i == 0)
		return (NULL);
	ft_putchar('\n');
	return (move);
}

t_path				*move_ant(t_data *data, t_path *paths, t_path *move)
{
	t_path		*tmp;
	t_path		*res;
	int			i;

	i = 0;
	tmp = paths;
	res = move;
	move = select_path(move);
	while (tmp && (data->ant_count >= tmp->size || i == 0) &&
			data->ant_count > 0)
	{
		i = 1;
		move = get_next_move(data, tmp->path, move);
		tmp = tmp->next;
		if (!res)
			res = move;
	}
	res = display_move(res);
	return (res);
}
