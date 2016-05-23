/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/06 13:38:34 by sganon            #+#    #+#             */
/*   Updated: 2016/05/11 17:21:35 by sganon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void	plane_intersect(t_objs *obj, t_env *e, int shadow)
{
	t_vector	n;
	t_vector	v;
	double		n_scalar_v;
	double		n_scalar_vector;
	t_cam		cam;

	if (shadow == 1)
		cam = e->light_inter;
	else
		cam = e->cam;
	v.x = cam.x;
	v.y = cam.y;
	v.z = cam.z;
	n.x = obj->x;
	n.y = obj->y;
	n.z = obj->z;
	n = rotate_x(n, e, obj->rx);
	n = rotate_y(n, e, obj->ry);
	n = rotate_z(n, e, obj->rz);
	v = rotate_x(v, e, cam.rx);
	v = rotate_y(v, e, cam.ry);
	v = rotate_z(v, e, cam.rz);
	n_scalar_v = vector_scalar(n, v);
	if (shadow == 1)
		n_scalar_vector = vector_scalar(n, e->lvector);
	else
		n_scalar_vector = vector_scalar(n, e->vector);
	if (n_scalar_vector > 0)
	{
		obj->s1 = (n_scalar_v + 3.) / n_scalar_vector;
		obj->s2 = INT_MAX;
	}
	else
	{
		obj->s1 = INT_MAX;
		obj->s2 = INT_MAX;
	}
}
