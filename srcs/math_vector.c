/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_vector.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/02 17:40:33 by sganon            #+#    #+#             */
/*   Updated: 2016/05/03 12:24:23 by sganon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

t_pos	new_vector(t_pos v1, t_pos v2)
{
	t_pos	new_vector;	
	new_vector.x = v1.x - v2.x;
	new_vector.y = v1.y - v2.y;
	new_vector.z = v1.z - v2.z;
	return (normalize_vector(new_vector));
}

t_pos	vector_double(t_pos v)
{
	t_pos new_vector;

	new_vector.x = 2. * v.x;
	new_vector.y = 2. * v.y;
	new_vector.y = 2. * v.y;
	return (normalize_vector(new_vector));
}

double	vector_scalar(t_pos v1, t_pos v2)
{
	double	scalar;

	scalar = (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
	return (scalar);
}
