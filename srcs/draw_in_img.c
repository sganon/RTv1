/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_in_img.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/20 16:58:00 by sganon            #+#    #+#             */
/*   Updated: 2016/05/20 16:58:03 by sganon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

static int		define_obj_color(t_objs *obj)
{
	if (obj->color == 0)
		return (0xFFFFFF);
	if (obj->color == 1)
		return (0xFF0000);
	if (obj->color == 2)
		return (0x00FF00);
	if (obj->color == 3)
		return (0x00ABFF);
	if (obj->color == 4)
		return (0xFFFF00);
	else
		return (0x9E9E9E);
}

void			draw_in_img(t_env *e, double cosi, t_objs *obj)
{
	int		p;
	t_color	u;

	if (cosi <= 0)
		cosi = 0;
	u.color = define_obj_color(obj);
	if (e->x < WIN_X && e->y < WIN_Y)
	{
		p = e->x * e->bpp / 8 + e->y * e->sl;
		e->img[p] = (u.rgb.r * (cosi));
		e->img[p + 1] = (u.rgb.g * (cosi));
		e->img[p + 2] = (u.rgb.b * (cosi));
	}
}
