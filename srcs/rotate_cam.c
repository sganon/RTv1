/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_cam.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/24 16:20:46 by sganon            #+#    #+#             */
/*   Updated: 2016/05/24 16:20:48 by sganon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_cam	rotate_cam_z(t_cam cam, t_env *e)
{
	double	old_x;
	double	old_y;
	double	rot;

	rot = cam.rz * 100.0;
	rot = rot >= 36000.0 ? rot - 36000.0 : rot;
	rot = rot < 0 ? rot + 36000.0 : rot;
	old_y = cam.y;
	old_x = cam.x;
	cam.x = (old_x * e->cos[(int)rot]) + (old_y * -(e->sin[(int)rot]));
	cam.y = (old_x * e->sin[(int)rot]) + (old_y * e->cos[(int)rot]);
	return (cam);
}

t_cam	rotate_cam_y(t_cam cam, t_env *e)
{
	double	old_x;
	double	old_z;
	double	rot;

	rot = cam.ry * 100.0;
	rot = rot >= 36000.0 ? rot - 36000.0 : rot;
	rot = rot < 0 ? rot + 36000.0 : rot;
	old_x = cam.x;
	old_z = cam.z;
	cam.x = (old_x * e->cos[(int)rot]) + (old_z * e->sin[(int)rot]);
	cam.z = (old_x * -(e->sin[(int)rot])) + (old_z * e->cos[(int)rot]);
	return (cam);
}

t_cam	rotate_cam_x(t_cam cam, t_env *e)
{
	double	old_y;
	double	old_z;
	double	rot;

	rot = cam.rx * 100.0;
	rot = rot >= 36000.0 ? rot - 36000.0 : rot;
	rot = rot < 0 ? rot + 36000.0 : rot;
	old_y = cam.y;
	old_z = cam.z;
	cam.y = (old_y * e->cos[(int)rot]) + (old_z * -(e->sin[(int)rot]));
	cam.z = (old_y * e->sin[(int)rot]) + (old_z * e->cos[(int)rot]);
	return (cam);
}

t_cam	rotate_cam(t_cam cam, t_env *e)
{
	cam = rotate_cam_x(cam, e);
	cam = rotate_cam_y(cam, e);
	cam = rotate_cam_z(cam, e);
	return (cam);
}
