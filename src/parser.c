/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/27 10:56:11 by tguillem          #+#    #+#             */
/*   Updated: 2016/05/03 02:09:00 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int		parse_room(t_data *data, char *str)
{
	char	**split;
	int		i;
	t_node	*node;

	i = 0;
	split = ft_strsplit(str, ' ');
	while (split[i])
	{
		if (i > 2 || (i > 0 && !ft_isstrnum(split[i])) ||
			!ft_isstralnum(split[i]))
			return (1);
		i++;
	}
	node = new_node(split[0], ft_atoi(split[1]), ft_atoi(split[1]));
	data->nodes = init_nodelst(data->nodes, node);
	if (data->command_flag == 1 && !data->start)
		data->start = node;
	else if (data->command_flag == 2 && !data->end)
		data->end = node;
	data->command_flag = 0;
	return (0);
}

static int		parse_connection(t_data *data, char *str)
{
	char			**split;

	split = ft_strsplit(str, '-');
	data->connections = init_connection(data->connections, split[0], split[1]);
	return (0);
}

static int		parse_line(t_data *data, int index, char *str)
{
	char	*tmp;

	if (!*str)
		return (1);
	if (!index)
		data->ant_count = ft_atoi(str);
	else
	{
		if (!ft_strncmp(str, "##", 2))
			data->command_flag = !ft_strcmp(str, "start") ? 2 :
				!ft_strcmp(str, "end");
		else if (!ft_strchr(str, '#') && !(ft_strchr(str, '#')))
		{
			if ((tmp = ft_strchr(str, ' ')) && ft_strchr(tmp + 1, ' ') ==
				ft_strrchr(tmp + 1, ' '))
				return (parse_room(data, str));
			else if ((tmp = ft_strchr(str, '-')) && tmp == ft_strrchr(str, '-'))
				return (parse_connection(data, str));
			else
				return (1);
		}
		else
			return (1);
	}
	return (0);
}

void			*parse_stdin(t_data *data)
{
	char	*buffer;
	int		index;

	index = 0;
	while (get_next_line(0, &buffer) == 1)
	{
		if ((!index && !ft_isstrnum(buffer)))
			break ;
		if (parse_line(data, index, buffer))
			break ;
		ft_printf("%s\n", buffer);
		index++;
	}
	return (NULL);
}
