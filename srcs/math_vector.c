/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_vector.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/02 17:40:33 by sganon            #+#    #+#             */
/*   Updated: 2016/05/07 17:03:53 by sganon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

t_vector	cam_object_vector(t_cam cam, t_objs *obj, t_env *e, int shadow)
{
	t_vector	new_vector;

	new_vector.x = cam.x - obj->x;
	new_vector.y = cam.y - obj->y;
	new_vector.z = cam.z - obj->z;
	if (shadow == 2)
	{
		new_vector = rotate_x(new_vector, e, e->cam.rx);
		new_vector = rotate_y(new_vector, e, e->cam.ry);
		new_vector = rotate_z(new_vector, e, e->cam.rz);
	}	
	new_vector = rotate_x(new_vector, e, cam.rx);
	new_vector = rotate_y(new_vector, e, cam.ry);
	new_vector = rotate_z(new_vector, e, cam.rz);
	return (new_vector);
}

t_vector	cam_plane_vector(t_cam cam, t_objs *obj, t_env *e)
{
	t_vector	new_vector;

	cam = rotate_cam(cam, e);
	new_vector.x = obj->x - cam.x;
	new_vector.y = obj->y - cam.y;
	new_vector.z = obj->z - cam.z;
	new_vector = rotate_x(new_vector, e, cam.rx);
	new_vector = rotate_y(new_vector, e, cam.ry);
	new_vector = rotate_z(new_vector, e, cam.rz);
	return (new_vector);
}

t_vector	cam_light_vector(t_cam cam, t_light *light)
{
	t_vector	new_vector;

	new_vector.x = cam.x - light->x;
	new_vector.y = cam.y - light->y;
	new_vector.z = cam.z - light->z;
	return (new_vector);
}

t_vector	new_vector(t_vector v1, t_vector v2)
{
	t_vector	new_vector;

	new_vector.x = v1.x - v2.x;
	new_vector.y = v1.y - v2.y;
	new_vector.z = v1.z - v2.z;
	return (new_vector);
}

double		vector_scalar(t_vector vect1, t_vector vect2)
{
	double		value;
	double		x;
	double		y;
	double		z;

	x = vect1.x * vect2.x;
	y = vect1.y * vect2.y;
	z = vect1.z * vect2.z;
	value = x + y + z;
	return (value);
}
