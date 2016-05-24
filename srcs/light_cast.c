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
	normal.x = obj->x;
	normal.y = obj->y;
	normal.z = obj->z;
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
	normal.x = e->light_inter.x - obj->x;
	if (obj->id == SPH)
		normal.y = e->light_inter.y - obj->y;
	normal.z = e->light_inter.z - obj->z;
	normal = normalize_vector(normal);
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

	cosi = 0.2;
	e->light = e->begin_light;
	while (e->light)
	{
		if (obj->id != PLA)
		{
			tmp = non_plan_light_cast(e, obj);
			cosi = tmp > cosi ? tmp : cosi;
		}
		else
		{
			tmp = plane_light_cast(e, obj);
			cosi = tmp > cosi ? tmp : cosi;
		}
		draw_in_img(e, cosi, obj);
		e->light = e->light->next;
	}
}
