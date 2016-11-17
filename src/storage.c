/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   storage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 08:56:37 by tguillem          #+#    #+#             */
/*   Updated: 2016/11/16 09:09:06 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int		check_number(char *line)
{
	int			i;

	i = 0;
	while (line[i])
	{
		if (!ft_isdigit(line[i]))
			return (0);
		i++;
	}
	i = ft_atoi(line);
	if (i <= 0)
		return (0);
	return (1);
}

static int		is_room(char *line)
{
	int			i;
	int			ret;

	ret = 0;
	i = 0;
	if (line[0] == 'L')
		return (0);
	while (line[i] && line[i] != ' ')
	{
		if (line[i] == '-')
			return (0);
		i++;
	}
	if (i != 0)
		ret = validate_block(line, &i);
	if (ret == 1)
		ret = validate_block(line, &i);
	if (ret == 1 && !line[i])
		return (1);
	return (0);
}

static int		is_valid_second(char *line, int *state)
{
	if (*state == 3 && is_room(line))
	{
		*state = 2;
		return (1);
	}
	else if (*state == 2 || *state == 4)
	{
		*state = 4;
		return (is_room_link(line));
	}
	return (0);
}

int				is_valid_line(char *line)
{
	static int	state = 0;

	if (is_excluded_command(line))
		return (1);
	if (state == 0)
	{
		state = 1;
		return (check_number(line));
	}
	else if (state == 1 || state == 2)
	{
		state = 2;
		if (ft_strncmp(line, "##start\0", 8) == 0
			|| ft_strncmp(line, "##end\0", 6) == 0)
		{
			state = 3;
			return (1);
		}
		if (is_room(line))
			return (1);
	}
	return (is_valid_second(line, &state));
}

void			store_map(t_array **data)
{
	char	*buffer;
	int		ret;

	buffer = NULL;
	while ((ret = get_next_line(0, &buffer)) > 0)
	{
		if (!buffer || !is_valid_line(buffer))
			break ;
		*data = array_init(*data, ft_strdup(buffer));
		ft_strdel(&buffer);
	}
	if (!*data || ret == -1)
		ft_memdel((void**)data);
	ft_strdel(&buffer);
}
