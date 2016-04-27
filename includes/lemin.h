/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/25 13:50:51 by tguillem          #+#    #+#             */
/*   Updated: 2016/04/27 17:27:07 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H
# include "libft.h"
# include <fcntl.h>
# include <unistd.h>

typedef struct			s_node
{
	char				*identifier;
	int					x;
	int					y;
	t_list				*neighboors;
}						t_node;

typedef struct			s_nodelst
{
	t_node				*data;
	struct s_nodelst	*next;
}						t_nodelst;

typedef struct			s_connection
{
	char				*room_one;
	char				*room_two;
	struct s_connection	*next;
}						t_connection;

typedef struct			s_data
{
	t_nodelst			*nodes;
	t_connection		*connections;
	t_node				*start;
	t_node				*end;
	int					ant_count;
	char				command_flag;
}						t_data;

t_data					*init_data(void);
void					destroy_data(t_data **data);
t_node					*new_node(char *identifier, int x, int y);
t_nodelst				*init_nodelst(t_nodelst *root, t_node *data);
t_connection			*init_connection(t_connection *root, char *room_one,
	char *room_two);
void					*parse_stdin(t_data *data);
#endif
