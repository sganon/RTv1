/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/11 17:09:31 by sganon            #+#    #+#             */
/*   Updated: 2016/05/11 17:21:35 by sganon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

static void	get_shadow_abc(t_env *e, t_objs *obj)
{
	t_vector	v;

	v = cam_object_vector(e->light_inter, obj);
	//v = rotate_obj(v, e, obj);
	if (obj->id == SPH)
	{
		e->a = pow(e->lvector.x, 2.) + pow(e->lvector.y, 2.) 
		+ pow(e->lvector.z, 2.);
		e->b = 2. * ((v.x * e->lvector.x) + (v.y * e->lvector.y) 
			+ (v.z * e->lvector.z));
		e->c = pow(v.x, 2.) + pow(v.y, 2.) + pow(v.z, 2.) - pow(obj->rayon, 2.);
	}
	if (obj->id == CYL)
	{
		e->a = pow(e->lvector.x, 2.) + pow(e->lvector.z, 2.);
		e->b = 2. * ((v.x * e->lvector.x) + (v.z * e->lvector.z));
		e->c = pow(v.x, 2.) + pow(v.z, 2.) - pow(obj->rayon, 2.);
	}
	if (obj->id == CON)
	{
		e->a = pow(e->lvector.x, 2.) - pow(e->lvector.y ,2.) 
		+ pow(e->lvector.z, 2.);
		e->b = 2. * ((v.x * e->lvector.x) - (v.y * e->lvector.y) 
			+ (v.z * e->lvector.z));
		e->c = pow(v.x, 2.) - pow(v.y, 2.) +
		pow(v.z, 2.);
	}
	if (obj->id != PLA)
		e->delta = e->b * e->b - 4. * e->a * e->c;
	else
		e->delta = 0;
}

int		shadow(t_objs *obj, t_env *e, int x, int y)
{
	t_objs	*closest;
	double	s;

	closest = NULL;
	s = INT_MAX;
	while (obj)
	{
		get_shadow_abc(e, obj);
		if (e->delta >= 0)
		{
			if (obj->id == PLA)
			{
				plane_intersect(obj, e, x, y);
			}
			else
			{
				obj->s1 = (-(e->b) + sqrt(e->delta)) / (2. * e->a);
				obj->s2 = (-(e->b) - sqrt(e->delta)) / (2. * e->a);
			}
			if ((obj->s1 >= 0 && obj->s1 < s) || (obj->s2 >= 0 && obj->s2 < s))
			{
				s = get_norme(obj);
				closest = obj;
			}
		}
		obj = obj->next;
	}
	if (closest)
		return (1);
	return (0);
}
