/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   abc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/20 16:39:01 by sganon            #+#    #+#             */
/*   Updated: 2016/05/20 16:39:03 by sganon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	sphere_abc(t_env *e, t_vector vector, t_vector v, t_objs *obj)
{
	e->a = pow(vector.x, 2.) + pow(vector.y, 2.) + pow(vector.z, 2.);
	e->b = 2. * ((v.x * vector.x) + (v.y * vector.y) + (v.z * vector.z));
	e->c = pow(v.x, 2.) + pow(v.y, 2.) + pow(v.z, 2.) - pow(obj->rayon, 2.);
}

static void	cylinder_abc(t_env *e, t_vector vector, t_vector v, t_objs *obj)
{
	e->a = pow(vector.x, 2.) + pow(vector.z, 2.);
	e->b = 2. * ((v.x * vector.x) + (v.z * vector.z));
	e->c = pow(v.x, 2.) + pow(v.z, 2.) - pow(obj->rayon, 2.);
}

static void	cone_abc(t_env *e, t_vector vector, t_vector v)
{
	e->a = pow(vector.x, 2.) - pow(vector.y, 2.) + pow(vector.z, 2.);
	e->b = 2. * ((v.x * vector.x) - (v.y * vector.y) + (v.z * vector.z));
	e->c = pow(v.x, 2.) - pow(v.y, 2.) + pow(v.z, 2.);
}

void		get_abc(t_env *e, t_objs *obj, int shadow)
{
	t_vector	v;
	t_vector	vec;

	if (shadow == 2)
	{
		vec = normalize_vector(rotate_obj(e->lvector, e, obj));
		v = cam_object_vector(e->light_inter, obj, e, shadow);
	}
	else
	{
		vec = normalize_vector(rotate_obj(e->vector, e, obj));
		v = cam_object_vector(e->cam, obj, e, shadow);
	}
	if (obj->id == SPH)
		sphere_abc(e, vec, v, obj);
	if (obj->id == CYL)
		cylinder_abc(e, vec, v, obj);
	if (obj->id == CON)
		cone_abc(e, vec, v);
	if (obj->id != PLA)
		e->delta = e->b * e->b - 4. * e->a * e->c;
	else
		e->delta = 0;
}
