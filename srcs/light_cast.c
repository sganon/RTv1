/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_cast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/20 17:03:33 by sganon            #+#    #+#             */
/*   Updated: 2016/05/20 17:03:34 by sganon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

static t_vector	get_normal(t_objs *obj, t_env *e)
{
	t_vector	normal;

	if (obj->id == SPH)
	{
		normal.x = e->light_inter.x - obj->x;
		normal.y = e->light_inter.y - obj->y;
		normal.z = e->light_inter.z - obj->z;
	}
	else if (obj->id == CON)
	{
		normal.x = (e->cam.x + (e->vector.x * get_norme(obj))) - obj->x;
		normal.y = (e->cam.y - (e->vector.y * get_norme(obj))) - obj->y;
		normal.z = (e->cam.z + (e->vector.z * get_norme(obj))) - obj->z;
	}
	else
	{
		normal.x = -(e->light_inter.x - e->vector.rx);
		normal.y = 0;
		normal.z = -(e->light_inter.z - e->vector.rz);
	}
	return (normalize_vector(normal));
}

static double	plane_light_cast(t_env *e, t_objs *obj)
{
	t_vector	normal;
	t_objs		*tmp;
	double		cosi;

	e->light_inter.x = (e->cam.x + (e->vector.x * obj->s1));
	e->light_inter.y = (e->cam.y + (e->vector.y * obj->s1));
	e->light_inter.z = (e->cam.z + (e->vector.z * obj->s1));
	e->lvector.x = e->light->x - e->light_inter.x;
	e->lvector.y = e->light->y - e->light_inter.y;
	e->lvector.z = e->light->z - e->light_inter.z;
	normal.x = obj->rx;
	normal.y = obj->ry;
	normal.z = obj->rz;
	normal = normalize_vector(normal);
	e->lvector = normalize_vector(e->lvector);
	obj->sh = 1;
	tmp = e->begin_list;
	cosi = 0.5 * fabs(vector_scalar(normal, e->lvector)) + specular_light(e, e->
		lvector, normal) * 0.5;
	if (shadow(tmp, e))
		return (cosi / 2);
	return (cosi);
}

static double	non_plan_light_cast(t_env *e, t_objs *obj)
{
	t_vector	normal;
	t_objs		*tmp;
	double		cosi;

	e->light_inter.x = (e->cam.x + (e->vector.x * get_norme(obj)));
	e->light_inter.y = (e->cam.y + (e->vector.y * get_norme(obj)));
	e->light_inter.z = (e->cam.z + (e->vector.z * get_norme(obj)));
	e->lvector.x = e->light->x - e->light_inter.x;
	e->lvector.y = e->light->y - e->light_inter.y;
	e->lvector.z = e->light->z - e->light_inter.z;
	normal = get_normal(obj, e);
	e->lvector = normalize_vector(e->lvector);
	obj->sh = 1;
	tmp = e->begin_list;
	cosi = 0.5 * vector_scalar(normal, e->lvector) + specular_light(e, e->
		lvector, normal) * 0.5;
	if (shadow(tmp, e))
		return (cosi / 2);
	return (cosi);
}

void			light_cast(t_env *e, t_objs *obj)
{
	double		cosi;
	double		tmp;
	int			i;

	cosi = 0.2;
	e->light = e->begin_light;
	i = 1;
	while (e->light)
	{
		if (obj->id != PLA)
			tmp = non_plan_light_cast(e, obj);
		else
			tmp = plane_light_cast(e, obj);
		tmp = tmp < 0 ? 0 : tmp;
		cosi = (cosi + tmp) / i > 1 ? 1 : (cosi + tmp) / i;
		i++;
		e->light = e->light->next;
	}
	draw_in_img(e, cosi, obj);
}
