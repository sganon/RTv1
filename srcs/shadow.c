/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/11 17:09:31 by sganon            #+#    #+#             */
/*   Updated: 2016/05/11 17:21:35 by sganon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

int		shadow(t_objs *obj, t_env *e)
{
	t_objs	*closest;
	double	s;

	closest = NULL;
	s = INT_MAX;
	while (obj)
	{
		get_abc(e, obj, 2);
		if (e->delta >= 0 && !obj->sh)
		{
			if (obj->id == PLA)
			{
				plane_intersect(obj, e, 1);
			}
			else
			{
				obj->s1 = (-(e->b) + sqrt(e->delta)) / (2. * e->a);
				obj->s2 = (-(e->b) - sqrt(e->delta)) / (2. * e->a);
			}
			if ((obj->s1 >= 0 && obj->s1 < s) || (obj->s2 >= 0 && obj->s2 < s))
			{
				s = get_norme(obj);
				closest = obj;
			}
		}
		if (obj->sh)
			obj->sh = 0;
		obj = obj->next;
	}
	if (closest)
		return (1);
	return (0);
}