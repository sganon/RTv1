/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/19 15:48:24 by sganon            #+#    #+#             */
/*   Updated: 2016/05/17 10:55:15 by sganon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

#include <stdio.h>

void	parse_coord(char *str, int step, t_objs *obj)
{
	if (step > 6 && obj->id != SPH && obj->id != CYL)
		ft_error("Too much argument for sphere declaration, expcted: 7", 2);
	if (step > 7 && (obj->id == SPH || obj->id == CYL))
		ft_error("Too much argument for object declaration, expcted: 8", 2);
	if (step == 0)
		obj->x = ft_atof(str);
	if (step == 1)
		obj->y = ft_atof(str);
	if (step == 2)
		obj->z = ft_atof(str);
	if (step == 3)
		obj->rx = ft_atof(str);
	if (step == 4)
		obj->ry = ft_atof(str);
	if (step == 5)
		obj->rz = ft_atoi(str);
	if (step == 6 && (obj->id == SPH || obj->id == CYL))
		obj->rayon = ft_atof(str);
	else if (step == 6)
		obj->color = ft_atof(str);
	if (step == 7 && (obj->id == SPH || obj->id == CYL))
		obj->color = ft_atof(str);
}

int		get_obj_type(char *str)
{
	if (str[0] == 's')
		return (6);
	if (str[0] == 'c' && str[1] == 'y')
		return (8);
	if (str[0] == 'c' && str[1] == 'o')
		return (4);
	if (str[0] == 'p')
		return (5);
	else
		return (0);
}
