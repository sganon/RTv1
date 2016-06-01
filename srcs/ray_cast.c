/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/02 17:13:56 by sganon            #+#    #+#             */
/*   Updated: 2016/05/17 12:17:48 by sganon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vector	normalize_vector(t_vector v)
{
	double	norme;

	norme = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	v.x /= norme;
	v.y /= norme;
	v.z /= norme;
	return (v);
}

t_vector	get_vector(t_vector vector, int x, int y)
{
	vector.x = -33. + (double)FOV / (double)WIN_X * (double)x;
	vector.y = 33. - (double)FOV / (double)WIN_Y * (double)y;
	vector.z = 60.;
	return (normalize_vector(vector));
}

double		get_norme(t_objs *obj)
{
	if (obj->s1 >= 0)
	{
		if (obj->s1 > obj->s2)
			return (obj->s2);
		else
			return (obj->s1);
	}
	else
		return (obj->s2);
}

void		get_intersect(t_objs *obj, t_env *e)
{
	t_objs	*closest;
	double	s;

	closest = NULL;
	s = INT_MAX - 1;
	while (obj)
	{
		get_abc(e, obj, 1);
		if (e->delta >= 0)
		{
			if (obj->id == PLA)
				plane_intersect(obj, e, 0);
			else
				store_hit(obj, e);
			if ((obj->s1 >= 0 && obj->s1 < s) || (obj->s2 >= 0 && obj->s2 < s))
			{
				s = get_norme(obj);
				closest = obj;
			}
		}
		obj = obj->next;
	}
	if (closest)
		light_cast(e, closest);
}

void		cast(t_env *e, t_objs *obj)
{
	e->y = 0;
	while (e->y < WIN_Y)
	{
		e->x = 0;
		while (e->x < WIN_X)
		{
			e->vector = get_vector(e->vector, e->x, e->y);
			get_intersect(obj, e);
			e->x++;
		}
		e->y++;
	}
}
