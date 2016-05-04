/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/02 17:13:56 by sganon            #+#    #+#             */
/*   Updated: 2016/05/04 20:05:54 by sganon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"
#include	<stdio.h>

void	draw_in_img(t_env *e, int x, int y, double cosi)
{
	int		p;
	t_color	u;
	double	k;

	k = 2;
	if (cosi <= 0)
		cosi = 0;
	printf("cosi: %f\n", cosi);
	u.color = 0x00FF00;
	if (x < WIN_X && y < WIN_Y)
	{
		p = x * e->bpp / 8 + y * e->sl;
		e->img[p] = u.rgb.r * (int)(cosi);
		e->img[p + 1] = u.rgb.g * (int)(cosi);
		e->img[p + 2] = u.rgb.b * (int)(cosi);
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

double	get_little(t_objs *obj)
{
	if (obj->s1 < obj->s2 && obj->s1 >= 0)
		return (obj->s1);
	else
		return (obj->s2);
}

void	get_color(t_env *e, t_objs *obj, int x, int y)
{
	double		dir;
	t_vector	vector_light;
	t_vector	normal;
	t_cam		light_pos;
	double		cosi;

	dir = get_little(obj);
	light_pos.x = (e->cam.x + (e->vector.x * dir));
	light_pos.y = (e->cam.y + (e->vector.y * dir));
	light_pos.z = (e->cam.z + (e->vector.z * dir));
	vector_light.x = e->light.x - (e->cam.x + (e->vector.x * dir));
	vector_light.y = e->light.y - (e->cam.y + (e->vector.y * dir));
	vector_light.z = e->light.z - (e->cam.z + (e->vector.z * dir));
	normal.x = ((e->cam.x + (e->vector.x * dir)) - obj->x);
	normal.y = ((e->cam.y + (e->vector.y * dir)) - obj->y);
	normal.z = ((e->cam.z + (e->vector.z * dir)) - obj->z);
	normalize_vector(normal);
	normalize_vector(vector_light);
	cosi = vector_scalar(normal, vector_light);
	draw_in_img(e, x, y, cosi);
}
void	get_intersect(t_objs *obj, t_env *e, int x, int y)
{
	double	delta;
	double	a;
	double	b;
	double	c;

	a = pow(e->vector.x, 2.) + pow(e->vector.y, 2.) + pow(e->vector.z, 2.);
	b = 2. * (((e->cam.x - obj->x) * e->vector.x) + ((e->cam.y - obj->y) * e->vector.y) + ((e->cam.z - obj->z) * e->vector.z));
	c = pow(e->cam.x - obj->x, 2.) + pow(e->cam.y - obj->y, 2.) + pow(e->cam.z - obj->z, 2.) - pow(obj->rayon, 2.);
	delta = b * b - 4. * a * c;
	if (delta < 0)
		return ;
	obj->s1 = (-b + sqrt(delta)) / (2. * a);
	obj->s2 = (-b - sqrt(delta)) / (2. * a);
	if (obj->s1 >= 0 || obj->s2 >= 0)
		get_color(e, obj, x, y);
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
				if (obj->id == SPH)
					get_intersect(obj, e, x, y);
				y++;
			}
			x++;
		}
		obj = obj->next;
	}
}
