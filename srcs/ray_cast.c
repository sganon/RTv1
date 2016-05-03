/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/02 17:13:56 by sganon            #+#    #+#             */
/*   Updated: 2016/05/03 20:37:21 by sganon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"
#include	<stdio.h>

void	draw_in_img(t_env *e, int x, int y)
{
	int		p;
	t_color	u;

	if (x < WIN_X && y < WIN_Y)
	{
		u.color = 0xFF0000;
		p = x * e->bpp / 8 + y * e->sl;
		e->img[p] = u.rgb.r;
		e->img[p + 1] = u.rgb.g;
		e->img[p + 2] = u.rgb.b;
	}
}

t_vector	normalize_vector(t_vector vector)
{
	double	norme;

	norme = sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
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

void	get_intersect(t_objs *obj, t_env *e, int x, int y)
{
	double	delta;
	double	a;
	double	b;
	double	c;

	a = e->vector.x * e->vector.x + e->vector.y * e->vector.y + e->vector.z * e->vector.z;
	b = 2. * (((e->cam.x - obj->x) * e->vector.x) + ((e->cam.y - obj->y) * e->vector.y) + ((e->cam.z - obj->z) * e->vector.z));
	c = pow(e->cam.x - obj->x, 2.) + pow(e->cam.y - obj->y, 2.) + pow(e->cam.z - obj->z, 2.) - pow(obj->rayon, 2.);
	delta = b * b - 4. * a * c;
	//	printf("a: %f\nb: %f\nc: %f\n", a, b, c);
	//	printf("delta: %f\n~~~~\n", delta);
	if (delta < 0)
		return ;
	obj->s1 = (-b + sqrt(delta)) / (2. * a);
	obj->s2 = (-b - sqrt(delta)) / (2. * a);
	//	printf("~~~~\ns1: %f\ns2: %f\n~~~~~\n", s1, s2);
	if (obj->s1 >= 0 || obj->s2 >= 0)
		draw_in_img(e, x, y);
}

void	cast(t_env *e, t_objs *obj)
{
	int	y;
	int	x;

	while (obj)
	{
		printf("id: %d\n", obj->id);
		x = 0;
		while (x < WIN_X)
		{
			y = 0;
			while (y < WIN_Y)
			{
				e->vector = get_vector(e->vector, x, y);
				//e->vector = rotate_vector(e->vector, obj, e);
				if (obj->id == 6)
					get_intersect(obj, e, x, y);
				y++;
			}
			x++;
		}
		obj = obj->next;
	}
}
