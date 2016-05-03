/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/02 17:13:56 by sganon            #+#    #+#             */
/*   Updated: 2016/05/03 13:58:03 by sganon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"
#include	<stdio.h>

void	draw_in_img(t_env *e, int x, int y)
{
	int	p;
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

t_pos	normalize_vector(t_pos vector)
{
	double	norme;

	norme = sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
	vector.x /= norme;
	vector.y /= norme;
	vector.z /= norme;
	return (vector);
}

t_pos	get_vector(t_pos vector, int x, int y)
{
	vector.x = -33.+ (double)FOV / (double)WIN_X * (double)x;
	vector.y = 33. - (double)FOV / (double)WIN_Y * (double)y;
	vector.z = 60.;
	return (normalize_vector(vector));
}

void	get_intersect(t_pos vector, t_objs *obj, t_env *e, int x, int y)
{
	double	delta;
	t_pos	d;
	double	s1;
	double	s2;
	double	a;
	double	b;
	double	c;
	
	d = new_vector(obj->pos_obj, obj->next->pos_obj);
	s1 = -1;
	s2 = -1;
	a = SQR(vector.x) + SQR(vector.y) + SQR(vector.z);
	b = 2. * ((d.x * vector.x) + (d.y * vector.y) + (d.z * vector.z));
	c = SQR(d.x) + SQR(d.y) + SQR(d.z) - SQR(obj->next->rayon);
//	a =  vector_scalar(vector, vector);
//	b = vector_scalar(vector_double(new_vector(obj->pos_obj, obj->next->pos_obj)), vector);
//	c = vector_scalar(new_vector(obj->pos_obj, obj->next->pos_obj), new_vector(obj->pos_obj, obj->next->pos_obj)) - (obj->next->rayon * obj->next->rayon);
	delta = SQR(b) - 4. * a * c;
//	printf("a: %f\nb: %f\nc: %f\n", a, b, c);
//	printf("delta: %f\n~~~~\n", delta);
	if (delta < 0)
		return ;
	s1 = (-b + sqrt(delta)) / (2. * a);
	s2 = (-b - sqrt(delta)) / (2. * a);
//	printf("~~~~\ns1: %f\ns2: %f\n~~~~~\n", s1, s2);
	if (s1 >= 0 || s2 >= 0)
		draw_in_img(e, x, y);
}

void	cast(t_env *e, t_objs *obj)
{
	int	y;
	int	x;
	t_pos	vector;

	x = 0;
	while (x < WIN_X)
	{
		y = 0;
		while (y < WIN_Y)
		{
			vector = get_vector(vector, x, y);
			vector = rotate_vector(vector, obj, e);
			//printf("vector_x: %f\nvector_y: %f\nvector_z: %f\n", vector.x, vector.y, vector.z);
			get_intersect(vector, obj, e, x, y);
			y++;
		}
		x++;
	}
}
