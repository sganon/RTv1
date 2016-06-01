/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/03 10:09:01 by sganon            #+#    #+#             */
/*   Updated: 2016/05/17 11:25:57 by sganon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vector	rotate_obj_z(t_vector vector, t_env *e, t_objs *obj)
{
	double	old_x;
	double	old_y;
	double	rot;

	rot = obj->rz * 100.0;
	rot = rot >= 36000.0 ? rot - 36000.0 : rot;
	rot = rot < 0 ? rot + 36000.0 : rot;
	old_y = vector.y;
	old_x = vector.x;
	vector.x = (old_x * e->cos[(int)rot]) + (old_y * -(e->sin[(int)rot]));
	vector.y = (old_x * e->sin[(int)rot]) + (old_y * e->cos[(int)rot]);
	return (vector);
}

t_vector	rotate_obj_y(t_vector vector, t_env *e, t_objs *obj)
{
	double	old_x;
	double	old_z;
	double	rot;

	rot = obj->ry * 100.0;
	rot = rot >= 36000.0 ? rot - 36000.0 : rot;
	rot = rot < 0 ? rot + 36000.0 : rot;
	old_x = vector.x;
	old_z = vector.z;
	vector.x = (old_x * e->cos[(int)rot]) + (old_z * e->sin[(int)rot]);
	vector.z = (old_x * -(e->sin[(int)rot])) + (old_z * e->cos[(int)rot]);
	return (vector);
}

t_vector	rotate_obj_x(t_vector vector, t_env *e, t_objs *obj)
{
	double	old_y;
	double	old_z;
	double	rot;

	rot = obj->rx * 100.0;
	rot = rot >= 36000.0 ? rot - 36000.0 : rot;
	rot = rot < 0 ? rot + 36000.0 : rot;
	old_y = vector.y;
	old_z = vector.z;
	vector.y = (old_y * e->cos[(int)rot]) + (old_z * -(e->sin[(int)rot]));
	vector.z = (old_y * e->sin[(int)rot]) + (old_z * e->cos[(int)rot]);
	return (vector);
}

t_vector	rotate_obj(t_vector vector, t_env *e, t_objs *obj)
{
	if (obj->id == SPH)
		return (vector);
	vector = rotate_obj_x(vector, e, obj);
	vector = rotate_obj_y(vector, e, obj);
	vector = rotate_obj_z(vector, e, obj);
	return (vector);
}
