/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_cam.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/10 12:24:27 by sganon            #+#    #+#             */
/*   Updated: 2016/05/12 14:54:22 by sganon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

t_cam		rotate_cam_z(t_env *e)
{
	double	old_x;
	double	old_y;
	double	rot;

	rot = e->cam.rx * 100.0;
	rot = rot >= 36000.0 ? rot - 36000.0 : rot;
	rot = rot < 0 ? rot + 36000.0 : rot;
	old_y = e->cam.y;
	old_x = e->cam.x;
	e->cam.x = (old_x * e->cos[(int)rot]) + (old_y * -(e->sin[(int)rot]));
	e->cam.y = (old_x * e->sin[(int)rot]) + (old_y * e->cos[(int)rot]);
	return (e->cam);
}

t_cam		rotate_cam_y(t_env *e)
{
	double	old_x;
	double	old_z;
	double	rot;

	rot = e->cam.ry * 100.0;
	rot = rot >= 36000 ? rot - 36000 : rot;
	rot = rot < 0 ? rot + 36000.0 : rot;
	old_x = e->cam.x;
	old_z = e->cam.z;
	e->cam.x = (old_x * e->cos[(int)rot]) + (old_z * e->sin[(int)rot]);
	e->cam.z = (old_x * -(e->sin[(int)rot])) + (old_z * e->cos[(int)rot]);
	return (e->cam);
}

t_cam		rotate_cam_x(t_env *e)
{
	double	old_y;
	double	old_z;
	double	rot;

	rot = e->cam.rx * 100.0;
	rot = rot >= 36000.0 ? rot - 36000.0 : rot;
	rot = rot < 0 ? rot + 36000.0 : rot;
	old_y = e->cam.y;
	old_z = e->cam.z;
	e->cam.y = (old_y * e->cos[(int)rot]) + (old_z * -(e->sin[(int)rot]));
	e->cam.z = (old_y * e->sin[(int)rot]) + (old_z * e->cos[(int)rot]);
	return (e->cam);
}

t_cam		rotate_cam(t_env *e)
{
	e->cam = rotate_cam_x(e);
	e->cam = rotate_cam_y(e);
	e->cam = rotate_cam_z(e);
	return (e->cam);
}
