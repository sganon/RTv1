/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/19 15:48:24 by sganon            #+#    #+#             */
/*   Updated: 2016/05/05 17:56:51 by sganon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

#include <stdio.h>

void	parse_coord(char *str, int step, t_objs *obj)
{
	if (step > 4 && obj->id == 6)
		ft_error("Too much argument for sphere declaration, expcted: 5", 2);
	if (step > 2 && obj->id < 6)
		ft_error("Too much argument for object declaration, expcted: 3", 2);
	if (step == 0)
		obj->x = ft_atoi(str);
	if (step == 1)
		obj->y = ft_atoi(str);
	if (step == 2)
		obj->z = ft_atoi(str);
	if (step == 3 && obj->id >= 6)
		obj->rayon = ft_atoi(str); 
	if (step == 4 && obj->id >= 6)
		obj->color = ft_atoi(str); 
}
