/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/06 13:38:34 by sganon            #+#    #+#             */
/*   Updated: 2016/05/11 17:21:35 by sganon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void	plane_intersect(t_objs *obj, t_env *e, int x, int y)
{
	t_vector	n;
	t_vector	v;
	double		n_scalar_v;
	double		n_scalar_vector;

	(void)x;
	(void)y;
	v.x = e->cam.x;
	v.y = e->cam.y;
	v.z = e->cam.z;
	n.x = obj->rx;
	n.y = obj->ry;
	n.z = obj->rz;
	n_scalar_v = vector_scalar(n, v);
	n_scalar_vector = vector_scalar(n, e->vector);
	if (n_scalar_vector > 0)
	{
		obj->s1 = (n_scalar_v + 3.) / n_scalar_vector;
		obj->s2 = INT_MAX;
	}
	else
	{
		obj->s1 = INT_MAX;
		obj->s2 = INT_MAX;
	}
}
