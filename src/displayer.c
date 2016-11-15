#include "lemin.h"

static void			select_path_next(char **new, t_path **run)
{
	char		*tmp;

	tmp = ft_strchr((*run)->path + 1, '-');
	if (tmp)
	{
		*new = ft_strdup(tmp);
		free((*run)->path);
		(*run)->path = *new;
	}
	else
	{
		free((*run)->path);
		(*run)->path = NULL;
	}
}

static t_path		*select_path(t_path *move)
{
	t_path		*run;
	char		*new;
	t_path		*prev;

	run = move;
	prev = NULL;
	while (run)
	{
		if (run->path)
			select_path_next(&new, &run);
		prev = run;
		run = run->next;
	}
	return (prev);
}

static void			display_move_next(t_path *run, int *i)
{
	char		*tmp;

	if (*i != 0)
		ft_putchar(' ');
	*i = 1;
	ft_putstr("L");
	ft_putnbr(run->size);
	if ((tmp = ft_strchr(run->path + 1, '-')))
		*tmp = '\0';
	ft_putstr(run->path);
	if (tmp)
		*tmp = '-';
}

static t_path		*display_move(t_path *move)
{
	int			i;
	t_path		*run;

	i = 0;
	run = move;
	while (run)
	{
		if (run->path)
			display_move_next(run, &i);
		run = run->next;
	}
	if (i == 0)
		return (NULL);
	ft_putchar('\n');
	return (move);
}

t_path		*move_ant(t_data *data, t_path *paths, t_path *move)
{
	t_path		*run;
	t_path		*res;
	int			i;

	i = 0;
	run = paths;
	res = move;
	move = select_path(move);
	while (run && (data->ant_count >= run->size || i == 0) && data->ant_count > 0)
	{
		i = 1;
		move = get_next_move(data, run->path, move);
		run = run->next;
		if (!res)
			res = move;
	}
	res = display_move(res);
	return (res);
}
