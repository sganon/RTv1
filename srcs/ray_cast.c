/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/02 17:13:56 by sganon            #+#    #+#             */
/*   Updated: 2016/05/07 17:05:37 by sganon           ###   ########.fr       */
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
	u.color = 0x00FF00;
	if (x < WIN_X && y < WIN_Y)
	{
		p = x * e->bpp / 8 + y * e->sl;
		e->img[p] = u.rgb.r * (cosi);
		e->img[p + 1] = u.rgb.g * (cosi);
		e->img[p + 2] = u.rgb.b * (cosi);
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

void	get_abc(t_env *e, t_objs *obj)
{
	if (obj->id == SPH)
	{
		e->a = pow(e->vector.x, 2.) + pow(e->vector.y, 2.) + pow(e->vector.z, 2.);
		e->b = 2. * (((e->cam.x - obj->x) * e->vector.x) + ((e->cam.y - obj->y) * e->vector.y) + ((e->cam.z - obj->z) * e->vector.z));
		e->c = pow(e->cam.x - obj->x, 2.) + pow(e->cam.y - obj->y, 2.) + pow(e->cam.z - obj->z, 2.) - pow(obj->rayon, 2.);
	}
	if (obj->id == CYL)
	{
		e->a = pow(e->vector.x, 2.) + pow(e->vector.z, 2.);
		e->b = 2. * (((e->cam.x - obj->x) * e->vector.x) + ((e->cam.z - obj->z) * e->vector.z));
		e->c = pow(e->cam.x - obj->x, 2.) + pow(e->cam.z - obj->z, 2.) - pow(obj->rayon, 2.);
	}
	if (obj->id == CON)
	{
		e->a = pow(e->vector.x, 2.) - pow(e->vector.y ,2.) + pow(e->vector.z, 2.);
		e->b = 2. * (((e->cam.x - obj->x) * e->vector.x) - ((e->cam.y - obj->y) * e->vector.y) + ((e->cam.z - obj->z) * e->vector.z));
		e->c = pow(e->cam.x - obj->x, 2.) - pow(e->cam.y - obj->y, 2.) +
			pow(e->cam.z - obj->z, 2.);
	}
}

double	get_norme(t_objs *obj)
{
	if (obj->s1 >= 0 && obj->s1 <= obj->s2)
		return (obj->s1);
	else
		return (obj->s2);
}

int		check_for_closer_obj(t_objs *obj, t_objs * tmp, t_env *e)
{
	double	tmp_n;
	double	obj_n;
	double	delta;

	obj_n = get_norme(obj);
	if (!tmp)
		return (0);
	else
	{
		get_abc(e, tmp);
		delta = e->b * e->b - 4. * e->a * e->c;
		if (delta < 0)
			return (check_for_closer_obj(obj, tmp->next, e));
		tmp->s1 = (-(e->b) + sqrt(delta)) / (2. * e->a);
		tmp->s2 = (-(e->b) - sqrt(delta)) / (2. * e->a);
		tmp_n = get_norme(tmp);
		if (tmp_n < obj_n)
			return (1);
	}
	return (check_for_closer_obj(obj, tmp->next, e));
}

void	get_color(t_env *e, t_objs *obj, int x, int y)
{
	double		dir;
	t_vector	vector_light;
	t_vector	normal;
	t_cam		light_inter;
	double		cosi;

	if (check_for_closer_obj(obj, e->begin_list, e))
		return ;
	dir = get_norme(obj);
	light_inter.x = (e->cam.x + (e->vector.x * dir));
	light_inter.y = (e->cam.y + (e->vector.y * dir));
	light_inter.z = (e->cam.z + (e->vector.z * dir));
	vector_light.x = e->light.x - light_inter.x;
	vector_light.y = e->light.y - light_inter.y;
	vector_light.z = e->light.z - light_inter.z;
	normal.x = ((light_inter.x) - obj->x);
	normal.y = ((light_inter.y) - obj->y);
	normal.z = ((light_inter.z) - obj->z);
	normal = normalize_vector(normal);
	vector_light = normalize_vector(vector_light);
	cosi = vector_scalar(normal, vector_light);
	draw_in_img(e, x, y, cosi);
}

void	get_intersect(t_objs *obj, t_env *e, int x, int y)
{
	double	delta;

	get_abc(e, obj);
	delta = e->b * e->b - 4. * e->a * e->c;
	if (delta < 0)
		return ;
	obj->s1 = (-(e->b) + sqrt(delta)) / (2. * e->a);
	obj->s2 = (-(e->b) - sqrt(delta)) / (2. * e->a);
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
			e->vector = get_vector(e->vector, x, y);
			y = 0;
			while (y < WIN_Y)
			{
				if (obj->id != PLA)
					get_intersect(obj, e, x, y);
				else
				{
					plane_intersect(obj, e, x, y);
				}
				y++;
			}
			x++;
		}
		obj = obj->next;
	}
}
