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

#include "rtv1.h"

int		extension(char *s)
{
	int len;

	len = ft_strlen(s);
	if (s[len - 1] == 't' && s[len - 2] == 'r' && s[len - 3] == '.')
		return (1);
	else
		return (0);
}

int		expose_hook(t_env *e)
{
	if (!e->img_ptr)
		create_image(e);
	cast(e, e->begin_list);
	mlx_do_sync(e->mlx);
	mlx_put_image_to_window(e->mlx, e->win, e->img_ptr, 0, 0);
	ft_bzero(e->img, (WIN_X * e->bpp / 8 + WIN_Y * e->sl));
	return (1);
}

t_objs	*manage_data(t_env *e, t_objs *obj)
{
	e->cam.x = obj->x;
	e->cam.y = obj->y;
	e->cam.z = obj->z;
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
			return (0);
		if (!extension(argv[1]))
			ft_error("File need .rt extension", 2);
		if (!(obj = parsing(argv[1], e, obj)))
			ft_error("Parsing error", 2);
		obj = manage_data(e, obj);
		e->begin_list = obj;
		mlx_expose_hook(e->win, expose_hook, e);
		mlx_key_hook(e->win, key_events, e);
		mlx_loop(e->mlx);
	}
	return (0);
}
