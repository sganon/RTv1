/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/18 18:15:17 by sganon            #+#    #+#             */
/*   Updated: 2016/05/09 16:39:45 by sganon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

int		init_trigo(t_env *e)
{
	int			i;
	double		rad;

	i = 0;
	e->cos = (double *)malloc(sizeof(double) * 36000);
	e->sin = (double *)malloc(sizeof(double) * 36000);
	e->tan = (double *)malloc(sizeof(double) * 36000);
	if (!e->cos || !e->sin || !e->tan)
		return (0);
	while (i < 36000)
	{
		rad = (((double)i / (100.0)) * (2.0) * M_PI) / (360.0);
		(e->cos)[i] = cos(rad);
		(e->sin)[i] = sin(rad);
		(e->tan)[i] = tan(rad);
		i++;
	}
	return (1);
}

int		create_image(t_env *e)
{
	e->img_ptr = mlx_new_image(e->mlx, WIN_X, WIN_Y);
	if (!e->img_ptr)
		return (0);
	e->img = mlx_get_data_addr(e->img_ptr, &(e->bpp), &(e->sl), &(e->end));
	return (1);
}

int		init_env(t_env *e)
{
	if (!(e->mlx = mlx_init()))
		return (0);
	e->win = mlx_new_window(e->mlx, WIN_X, WIN_Y, "RTv1");
	e->img_ptr = NULL;
	e->col.s1 = INT_MAX - 1;
	e->col.s2 = INT_MAX - 1;
	e->col.obj = NULL;
	e->light = (t_light *)malloc(sizeof(t_light *));
	e->begin_light = e->light;
	if (!init_trigo(e))
		return (0);
	return (1);
}
