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
/*
static	void	rotate(t_objs *obj, t_vector vector, t_vector pos, t_env *e)
{
	vector = rotate_x(vector, e, obj->rx);
	vector = rotate_y(vector, e, obj->ry);
	vector = rotate_z(vector, e, obj->rz);
	pos = rotate_x(pos, e, obj->x);
	pos = rotate_y(pos, e, obj->y);
	pos = rotate_z(pos, e, obj->z);
	vector.rx = pos.x;
	vector.ry = pos.y;
	vector.rz = pos.z;
}
*/
static void	sphere_abc(t_env *e, t_vector vector, t_vector v, t_objs *obj)
{
	e->a = pow(vector.x, 2.) + pow(vector.y, 2.) + pow(vector.z, 2.);
	e->b = 2. * ((v.x * vector.x) + (v.y * vector.y) + (v.z * vector.z));
	e->c = pow(v.x, 2.) + pow(v.y, 2.) + pow(v.z, 2.) - pow(obj->rayon, 2.);
}

static void	cylinder_abc(t_env *e, t_vector vector, t_vector v, t_objs *obj)
{
	//t_vector	pos;

	//pos.x = obj->x;
	//pos.y = obj->y;
	//pos.z = obj->z;
	//rotate(obj, e->vector, pos, e);
	e->a = pow(vector.x, 2.) + pow(vector.z, 2.);
	e->b = 2. * ((v.x * vector.x) + (v.z * vector.z));
	e->c = pow(v.x, 2.) + pow(v.z, 2.) - pow(obj->rayon, 2.);
}

static void	cone_abc(t_env *e, t_vector vector, t_vector v)
{
	e->a = pow(vector.x, 2.) - pow(vector.y ,2.) + pow(vector.z, 2.);
	e->b = 2. * ((v.x * vector.x) - (v.y * vector.y) + (v.z * vector.z));
	e->c = pow(v.x, 2.) - pow(v.y, 2.) + pow(v.z, 2.);
}

void	get_abc(t_env *e, t_objs *obj, int nb)
{
	t_vector	v;
	t_vector	vec;

	if(nb == 2)
	{
		vec = rotate_obj(e->lvector, e, obj);
		v = cam_object_vector(e->light_inter, obj, e);
	}
	else
	{
		vec = rotate_obj(e->vector, e, obj);
		v = cam_object_vector(e->cam, obj, e);
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