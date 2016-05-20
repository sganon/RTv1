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

#include "RTv1.h"

static void	sphere_abc(t_env *e, t_vector v, t_objs *obj)
{
	e->a = pow(e->vector.x, 2.) + pow(e->vector.y, 2.) + pow(e->vector.z, 2.);
	e->b = 2. * ((v.x * e->vector.x) + (v.y * e->vector.y) + (v.z * e->vector.z));
	e->c = pow(v.x, 2.) + pow(v.y, 2.) + pow(v.z, 2.) - pow(obj->rayon, 2.);
}

static void	cylinder_abc(t_env *e, t_vector v, t_objs *obj)
{
	e->a = pow(e->vector.x, 2.) + pow(e->vector.z, 2.);
	e->b = 2. * ((v.x * e->vector.x) + (v.z * e->vector.z));
	e->c = pow(v.x, 2.) + pow(v.z, 2.) - pow(obj->rayon, 2.);
}

static void	cone_abc(t_env *e, t_vector vm)
{
	e->a = pow(e->vector.x, 2.) - pow(e->vector.y ,2.) + pow(e->vector.z, 2.);
	e->b = 2. * ((v.x * e->vector.x) - (v.y * e->vector.y) + (v.z * e->vector.z));
	e->c = pow(v.x, 2.) - pow(v.y, 2.) + pow(v.z, 2.);
}

void	get_abc(t_env *e, t_objs *obj)
{
	t_vector	v;

	e->vector = rotate_obj(e->vector, e, obj);
	v = cam_object_vector(e->cam, obj);
	if (obj->id == SPH)
		sphere_abc(e, v, obj);
	if (obj->id == CYL)
		cylinder_abc(e, v, obj);
	if (obj->id == CON)
		cone_abc(e, v);
	if (obj->id != PLA)
		e->delta = e->b * e->b - 4. * e->a * e->c;
	else
		e->delta = 0;
}