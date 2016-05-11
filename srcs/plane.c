/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/06 13:38:34 by sganon            #+#    #+#             */
/*   Updated: 2016/05/11 15:49:10 by sganon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void	get_plane_color(t_env *e, t_objs *obj, int x, int y)
{
	double		dir;
	t_vector	vector_light;
	t_vector	normal;
	t_cam		light_inter;
	double		cosi;

	dir = obj->s1;
	light_inter.x = (e->cam.x + (e->vector.x * dir));
	light_inter.y = (e->cam.y + (e->vector.y * dir));
	light_inter.z = (e->cam.z + (e->vector.z * dir));
	vector_light.x = light_inter.x - e->light.x;
	vector_light.y = light_inter.y - e->light.y;
	vector_light.z = light_inter.z - e->light.z;
	normal.x = obj->x;
	normal.y = obj->y;
	normal.z = obj->z;
	normal = normalize_vector(normal);
	vector_light = normalize_vector(vector_light);
	cosi = fabs(vector_scalar(normal, vector_light));
	e->vector = vector_light;
	draw_in_img(e, x, y, cosi, obj);
}

void	plane_intersect(t_objs *obj, t_env *e, int x, int y)
{
	t_vector	n;
	t_vector	v;
	double		n_scalar_v;
	double		n_scalar_vector;

	(void)x;
	(void)y;
	v.x = e->cam.x;
	v.y = e->cam.y;
	v.z = e->cam.z;
	n.x = obj->x;
	n.y = obj->y;
	n.z = obj->z;
	n_scalar_v = vector_scalar(n, v);
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
