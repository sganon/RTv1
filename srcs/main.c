/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/18 18:11:00 by sganon            #+#    #+#             */
/*   Updated: 2016/05/12 16:20:10 by sganon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

#include <stdio.h>

void	print_list(t_objs *obj, t_env *e)
{
	printf("Camera(%f, %f, %f)\n", e->cam.x, e->cam.y, e->cam.z);
	printf("~~~~~~~~~~~~~~~~~\n");
	printf("Camera_rotate(%f, %f, %f)\n", e->cam.rx, e->cam.ry, e->cam.rz);
	while (obj)
	{
		printf("~~~~~~~~~~~~~~~~~\n");
		printf(" id: %d\n pos_x: %f\n pos_y: %f\n pos_z: %f rx: %f ry: %f rz: %f\n", obj->id, obj->x, obj->y, obj->z, obj->rx, obj->ry, obj->rz);
		if (obj->id == 6)
			printf(" rayon: %d\n", obj->rayon);
		printf("color: %d\n", obj->color);
		obj = obj->next;
	}
	printf("~~~~~~~~~~~~~~~~~\n");
	printf("Light(%f, %f, %f)\n", e->light.x, e->light.y, e->light.z);
}

int		expose_hook(t_env *e)
{
	if (!e->img_ptr)
		create_image(e);
	cast(e, e->begin_list);
	mlx_put_image_to_window(e->mlx, e->win, e->img_ptr, 0, 0);
	mlx_do_sync(e->mlx);
	return (1);
}

t_objs	*manage_data(t_env *e, t_objs *obj)
{
	e->cam.x = obj->x;
	e->cam.y = obj->y;
	e->cam.y = obj->z;
	e->cam.rx = obj->rx;
	e->cam.ry = obj->ry;
	e->cam.rz = obj->rz;
	if (obj->next)
		obj = obj->next;
	return (obj);
}

int		main(int argc, char **argv)
{
	t_env	*e;
	t_objs	*obj;

	if (argc == 2)
	{
		e = (t_env *)malloc(sizeof(t_env));
		obj = (t_objs *)malloc(sizeof(t_objs));
		if (!(init_env(e)))
			return(0);
		obj = parsing(argv[1], e, obj);
		obj = manage_data(e, obj);
		print_list(obj, e);
		e->begin_list = obj;
		mlx_expose_hook(e->win, expose_hook, e);
		mlx_key_hook(e->win, key_events, e);
		mlx_loop(e->mlx);
	}
	return (0);
}
