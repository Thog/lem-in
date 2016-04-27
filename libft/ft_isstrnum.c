/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isstrnum.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/27 15:46:23 by tguillem          #+#    #+#             */
/*   Updated: 2016/04/27 15:46:41 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				ft_isstrnum(char *str)
{
	if (!str || !*str)
		return (0);
	while (*str)
		if (!ft_isalnum(*str++))
			return (0);
	return (1);
}
