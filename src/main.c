/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/25 13:28:14 by tguillem          #+#    #+#             */
/*   Updated: 2016/04/27 12:17:01 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		main(void)
{
	t_data		*data;

	data = init_data();
	parse_stdin(data);
	destroy_data(&data);
	return (0);
}
