/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_cast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/20 17:03:33 by sganon            #+#    #+#             */
/*   Updated: 2016/05/20 17:03:34 by sganon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

static double	plane_light_cast(t_env *e, t_objs *obj)
{
	t_vector	vector_light;
	t_vector	normal;
	t_cam		light_inter;


	light_inter.x = (e->cam.x + (e->vector.x * obj->s1));
	light_inter.y = (e->cam.y + (e->vector.y * obj->s1));
	light_inter.z = (e->cam.z + (e->vector.z * obj->s1));
	vector_light.x = light_inter.x - e->light->x;
	vector_light.y = light_inter.y - e->light->y;
	vector_light.z = light_inter.z - e->light->z;
	normal.x = obj->x;
	normal.y = obj->y;
	normal.z = obj->z;
	normal = normalize_vector(normal);
	vector_light = normalize_vector(vector_light);
	e->light_inter = light_inter;
	return (fabs(vector_scalar(normal, vector_light)));
}

static double	sphere_and_cylinder_light_cast(t_env *e, t_objs *obj)
{
	t_vector	vector_light;
	t_vector	normal;
	t_cam		light_inter;

	light_inter.x = (e->cam.x + (e->vector.x * get_norme(obj)));
	light_inter.y = (e->cam.y + (e->vector.y * get_norme(obj)));
	light_inter.z = (e->cam.z + (e->vector.z * get_norme(obj)));
	vector_light.x = e->light->x - light_inter.x;
	vector_light.y = e->light->y - light_inter.y;
	vector_light.z = e->light->z - light_inter.z;
	normal.x = ((light_inter.x) - obj->x);
	normal.y = ((light_inter.y) - obj->y);
	if (obj->id == CYL)
		normal.y = 0;
	normal.z = ((light_inter.z) - obj->z);
	normal = normalize_vector(normal);
	vector_light = normalize_vector(vector_light);
	e->light_inter = light_inter;
	return (vector_scalar(normal, vector_light));	
}

static double	cone_light_cast(t_env *e, t_objs *obj)
{
	t_vector	vector_light;
	t_vector	normal;

	vector_light.x = e->light->x - (e->cam.x + (e->vector.x * get_norme(obj)));
	vector_light.y = e->light->y - (e->cam.y + (e->vector.y * get_norme(obj)));
	vector_light.z = e->light->z - (e->cam.z + (e->vector.z * get_norme(obj)));
	normal.x = ((e->cam.x + (e->vector.x * get_norme(obj))) - obj->x);
	normal.y = ((e->cam.y - (e->vector.y * get_norme(obj))) - obj->y);
	normal.z = ((e->cam.z + (e->vector.z * get_norme(obj))) - obj->z);
	normal = normalize_vector(normal);
	vector_light = normalize_vector(vector_light);
	return (vector_scalar(normal, vector_light));
}

void	light_cast(t_env *e, t_objs *obj, int x, int y)
{
	int			i;
	double		cosi;

	cosi = 0;
	i = 1;
	e->light = e->begin_light;
	while(e->light)
	{
		if (obj->id == SPH || obj->id == CYL)
			cosi = sphere_and_cylinder_light_cast(e, obj) > cosi ? sphere_and_cylinder_light_cast(e, obj) : cosi;
		else if (obj->id == CON)
			cosi = cone_light_cast(e, obj) > cosi ? cone_light_cast(e, obj) : cosi;
		else if (obj->id == PLA)
			cosi = plane_light_cast(e, obj) > cosi ? plane_light_cast(e, obj) : cosi;
		i++;
		draw_in_img(e, x, y, cosi, obj);
		e->light = e->light->next;
	}
}