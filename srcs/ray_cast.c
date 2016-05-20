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

int		define_obj_color(t_objs *obj)
{
	if (obj->color == 0)
		return (0xFFFFFF);
	if (obj->color == 1)
		return (0xFF0000);
	if (obj->color == 2)
		return (0x00FF00);
	if (obj->color == 3)
		return (0x0000FF);
	if (obj->color == 4)
		return (0xFFFF00);
	else
		return (0x9E9E9E);
}

void	draw_in_img(t_env *e, int x, int y, double cosi, t_objs *obj)
{
	int		p;
	t_color	u;
	double	k;

	k = 2;
	if (cosi <= 0)
		cosi = 0;
//	if (shadow(e->begin_list, e, x, y))
//		return ;
	u.color = define_obj_color(obj);
	if (x < WIN_X && y < WIN_Y)
	{
		p = x * e->bpp / 8 + y * e->sl;
		e->img[p] = (u.rgb.r * (cosi));
		e->img[p + 1] = (u.rgb.g * (cosi));
		e->img[p + 2] = (u.rgb.b * (cosi));
	}
}

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


void	get_color(t_env *e, t_objs *obj, int x, int y)
{
	t_vector	vector_light;
	t_vector	normal;
	t_cam		light_inter;
	double		cosi;
	int			i;

	if (obj->id == PLA)
	{
		get_plane_color(e, obj, x, y);
		return;
	}
	cosi = 0;
	i = 1;
	e->light = e->begin_light;
	while(e->light)
	{
		light_inter.x = (e->cam.x + (e->vector.x * get_norme(obj)));
		light_inter.y = (e->cam.y + (e->vector.y * get_norme(obj)));
		light_inter.z = (e->cam.z + (e->vector.z * get_norme(obj)));
		vector_light.x = e->light->x - light_inter.x;
		vector_light.y = e->light->y - light_inter.y;
		vector_light.z = e->light->z - light_inter.z;
		normal.x = ((light_inter.x) - obj->x);
		normal.y = ((light_inter.y) - obj->y);
		normal.z = ((light_inter.z) - obj->z);
		normal = normalize_vector(normal);
		vector_light = normalize_vector(vector_light);
		cosi = (cosi + vector_scalar(normal, vector_light)) / i > cosi ? (cosi + vector_scalar(normal, vector_light)) / i : cosi;
		i++;
		e->lvector = cam_light_vector(light_inter, e->light);
		e->light_inter = light_inter;
		draw_in_img(e, x, y, cosi, obj);
		e->light = e->light->next;
	}
}

void	get_intersect(t_objs *obj, t_env *e, int x, int y)
{

	t_objs	*closest;
	double	s;

	closest = NULL;
	s = INT_MAX;
	while (obj)
	{
		get_abc(e, obj);
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
		get_color(e, closest, x, y);
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
			e->vector = rotate_vector(e->vector, e);
			get_intersect(obj, e, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(e->mlx, e->win, e->img_ptr, 0, 0);
}
