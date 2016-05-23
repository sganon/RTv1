/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/03 10:09:01 by sganon            #+#    #+#             */
/*   Updated: 2016/05/17 11:18:12 by sganon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

t_vector	rotate_z(t_vector vector, t_env *e, double rot)
{
	double	old_x;
	double	old_y;

	rot = rot * 100;
	rot = rot >= 36000.0 ? rot - 36000.0 : rot;
	rot = rot < 0 ? rot + 36000.0 : rot;
	old_y = vector.y;
	old_x = vector.x;
	vector.x = (old_x * e->cos[(int)rot]) + (old_y * -(e->sin[(int)rot]));
	vector.y = (old_x * e->sin[(int)rot]) + (old_y * e->cos[(int)rot]);
	return (vector);
}

t_vector	rotate_y(t_vector vector, t_env *e, double rot)
{
	double	old_x;
	double	old_z;

	rot = rot * 100;
	rot = rot >= 36000.0 ? rot - 36000.0 : rot;
	rot = rot < 0 ? rot + 36000.0 : rot;
	old_x = vector.x;
	old_z = vector.z;
	vector.x = (old_x * e->cos[(int)rot]) + (old_z * e->sin[(int)rot]);
	vector.z = (old_x * -(e->sin[(int)rot])) + (old_z * e->cos[(int)rot]);
	return (vector);
}

t_vector	rotate_x(t_vector vector, t_env *e, double rot)
{
	double	old_y;
	double	old_z;

	rot = rot * 100;
	rot = rot >= 36000.0 ? rot - 36000.0 : rot;
	rot = rot < 0 ? rot + 36000.0 : rot;
	old_y = vector.y;
	old_z = vector.z;
	vector.y = (old_y * e->cos[(int)rot]) + (old_z * -(e->sin[(int)rot]));
	vector.z = (old_y * e->sin[(int)rot]) + (old_z * e->cos[(int)rot]);
	return (vector);
}
