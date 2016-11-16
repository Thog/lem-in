/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 08:55:48 by tguillem          #+#    #+#             */
/*   Updated: 2016/11/16 09:02:06 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int			ft_count_char(char *str, char c)
{
	int	i;

	i = 0;
	while (*str)
	{
		if (*str == c)
			i++;
		str++;
	}
	return (i);
}

char		*ft_strfjoin(char const *s1, char const *s2)
{
	char		*res;

	res = ft_strjoin(s1, s2);
	free((void*)s1);
	return (res);
}

void		display_one_path(t_path *path, int ant)
{
	int			i;
	char		*tmp;

	i = 0;
	tmp = ft_strchr(path->path, '-');
	while (i < ant)
	{
		if (i != 0)
			ft_putchar(' ');
		i++;
		ft_putstr("L");
		ft_putnbr(i);
		ft_putstr(tmp);
	}
	ft_putendl("");
}

t_path		*get_next_move(t_data *data, char *path, t_path *move)
{
	static int	i = 1;
	char		*str;
	char		*tmp1;
	t_path		*new;

	new = ft_memalloc(sizeof(t_path));
	new->next = NULL;
	new->size = i;
	tmp1 = ft_strchr(path, '-');
	str = ft_strdup(tmp1);
	new->path = str;
	data->ant_count--;
	i++;
	if (!move)
		return (new);
	move->next = new;
	return (new);
}
