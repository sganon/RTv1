/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/03 10:09:01 by sganon            #+#    #+#             */
/*   Updated: 2016/05/05 17:43:58 by sganon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

t_vector	rotate_z(t_vector vector, t_objs *obj, t_env *e)
{
	double	old_x;
	double	old_y;
	double	rot;

	rot = obj->rx * 10000.0;
	rot = rot >= 36000.0 ? rot - 36000.0 : rot;
	rot = rot < 0 ? rot + 36000.0 : rot;
	old_y = vector.y;
	old_x = vector.x;
	vector.x = (old_x * e->cos[(int)rot]) + (old_y * -(e->sin[(int)rot]));
	vector.y = (old_x * e->sin[(int)rot]) + (old_y * e->cos[(int)rot]);
	return (vector);
}

t_vector	rotate_y(t_vector vector, t_objs *obj, t_env *e)
{
	double	old_x;
	double	old_z;
	double	rot;

	rot = obj->ry * 10000.0;
	rot = rot >= 36000.0 ? rot - 36000.0 : rot;
	rot = rot < 0 ? rot + 36000.0 : rot;
	old_x = vector.x;
	old_z = vector.z;
	vector.x = (old_x * e->cos[(int)rot]) + (old_z * e->sin[(int)rot]);
	vector.z = (old_x * -(e->sin[(int)rot])) + (old_z * e->cos[(int)rot]);
	return (vector);
}

t_vector	rotate_x(t_vector vector, t_objs *obj, t_env *e)
{
	double	old_y;
	double	old_z;
	double	rot;

	rot = obj->rx * 10000.0;
	rot = rot >= 36000.0 ? rot - 36000.0 : rot;
	rot = rot < 0 ? rot + 36000.0 : rot;
	old_y = vector.y;
	old_z = vector.z;
	vector.y = (old_y * e->cos[(int)rot]) + (old_z * -(e->sin[(int)rot]));
	vector.z = (old_y * e->sin[(int)rot]) + (old_z * e->cos[(int)rot]);
	return (vector);
}

t_vector	rotate_vector(t_vector vector, t_objs *obj, t_env *e)
{
	vector = rotate_x(vector, obj, e);
	vector = rotate_y(vector, obj, e);
	vector = rotate_z(vector, obj, e);
	return (vector);
}
