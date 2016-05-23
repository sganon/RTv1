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

static t_cam	get_cam(t_env *e, int shadow)
{
	if (shadow == 1)
		return (e->light_inter);
	else
		return (e->cam);
}

static double	get_n_scalar_vector(t_env *e, t_vector n, int shadow)
{
	if (shadow == 1)
		return (vector_scalar(n, e->lvector));
	else
		return (vector_scalar(n, e->vector));
}

void			plane_intersect(t_objs *obj, t_env *e, int shadow)
{
	t_vector	n;
	t_vector	v;
	double		n_scalar_v;
	double		n_scalar_vector;
	t_cam		cam;

	cam = get_cam(e, shadow);
	v.x = cam.x;
	v.y = cam.y;
	v.z = cam.z;
	v = rotate_obj(v, e, obj);
	n.x = obj->x;
	n.y = obj->y;
	n.z = obj->z;
	n = rotate_obj(n, e, obj);
	n_scalar_vector = get_n_scalar_vector(e, n, shadow);
	n_scalar_v = vector_scalar(n, v);
	if (n_scalar_vector > 0)
		obj->s1 = (n_scalar_v + 3.) / n_scalar_vector;
	else
		obj->s1 = INT_MAX;
	obj->s2 = INT_MAX;
}
