/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/27 10:56:11 by tguillem          #+#    #+#             */
/*   Updated: 2016/04/27 17:26:08 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int		parse_room(t_data *data, char *line)
{
	char	**split;
	int		i;
	t_node	*node;

	i = 0;
	split = ft_strsplit(line, ' ');
	while (split[i])
	{
		if (i > 2 || (i > 0 && !ft_isstrnum(split[i])))
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

static int		parse_connection(t_data *data, char *line)
{
	char			**split;

	split = ft_strsplit(line, '-');
	data->connections = init_connection(data->connections, split[0], split[1]);
	return (0);
}

static int		parse_line(t_data *data, int index, char *line)
{
	char	*tmp;

	if (!*line)
		return (1);
	if (!index)
		data->ant_count = ft_atoi(line);
	else
	{
		if (!ft_strncmp(line, "##", 2))
			data->command_flag = !ft_strcmp(line, "start") ? 2 :
				!ft_strcmp(line, "end");
		else if (!ft_strchr(line, '#') && !(ft_strchr(line, '#')))
		{
			if ((tmp = ft_strchr(line, ' ')) && ft_strchr(tmp, ' ') ==
				ft_strrchr(tmp, ' '))
				return (parse_room(data, line));
			else if (ft_strchr(line, '-') == ft_strrchr(line, '-'))
				return (parse_connection(data, line));
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
		if (parse_line(data, index, buffer))
			break ;
		ft_printf("%s\n", buffer);
		index++;
	}
	return (NULL);
}
