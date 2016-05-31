/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specular.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/24 11:26:43 by sganon            #+#    #+#             */
/*   Updated: 2016/05/24 11:26:45 by sganon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

static t_vector	get_ref(t_vector light, t_vector normal, t_env *e)
{
	t_vector	ref;
	double		d_dot;

	d_dot = 2.0 * vector_scalar(light, normal);
	ref.x = light.x - d_dot * normal.x;
	ref.y = light.y - d_dot * normal.y;
	ref.z = light.z - d_dot * normal.z;
	ref = rotate_x(ref, e, e->cam.rx);
	ref = rotate_y(ref, e, e->cam.ry);
	ref = rotate_z(ref, e, e->cam.rz);
	return (normalize_vector(ref));
}

double			specular_light(t_env *e, t_vector light, t_vector normal)
{
	t_vector	ref;
	double		dot;

	ref = get_ref(light, normal, e);
	dot = vector_scalar(e->vector, ref);
	if (dot > 0)
		return (powf(dot, 200));
	else
		return (0);
}
