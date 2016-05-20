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

#include "RTv1.h"
#include	<stdio.h>

t_vector	normalize_vector(t_vector vector)
{
	double	norme;

	norme = sqrt(vector.x * vector.x + vector.y * vector.y + vector.z 
		* vector.z);
	vector.x /= norme;
	vector.y /= norme;
	vector.z /= norme;
	return (vector);
}

t_vector	get_vector(t_vector vector, int x, int y)
{
	vector.x = -33. + (double)FOV / (double)WIN_X * (double)x;
	vector.y = 33. - (double)FOV / (double)WIN_Y * (double)y;
	vector.z = 60.;
	return (normalize_vector(vector));
}


double	get_norme(t_objs *obj)
{
	if (obj->s1 >= 0 && obj->s1 <= obj->s2)
		return (obj->s1);
	else
		return (obj->s2);
}

void	get_intersect(t_objs *obj, t_env *e, int x, int y)
{

	t_objs	*closest;
	double	s;

	closest = NULL;
	s = INT_MAX;
	while (obj)
	{
		get_abc(e, obj, 1);
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
		light_cast(e, closest, x, y);
}

void	cast(t_env *e, t_objs *obj)
{
	int	y;
	int	x;

	y = 0;
	while (y < WIN_Y)
	{
		x = 0;
		while (x < WIN_X)
		{
			e->vector = get_vector(e->vector, x, y);
			e->vector = rotate_x(e->vector, e, e->cam.rx);
			e->vector = rotate_y(e->vector, e, e->cam.ry);
			e->vector = rotate_y(e->vector, e, e->cam.rz);
			get_intersect(obj, e, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(e->mlx, e->win, e->img_ptr, 0, 0);
}
