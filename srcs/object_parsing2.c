/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/19 15:48:24 by sganon            #+#    #+#             */
/*   Updated: 2016/04/29 18:47:37 by sganon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

#include <stdio.h>

void	parse_coord(char *str, int step, t_objs *obj)
{
	printf("step: %d  buffer: %s\n", step, str);
	if (step == 0)
		obj->pos_obj.x = ft_atoi(str);
	if (step == 1)
		obj->pos_obj.y = ft_atoi(str);
	if (step == 2)
		obj->pos_obj.z = ft_atoi(str);
	if (step == 3 && obj->id == 6)
		obj->rayon = ft_atoi(str); 
	if (step == 4 && obj->id == 6)
		obj->color = ft_atoi(str); 
}
