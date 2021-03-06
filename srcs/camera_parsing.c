/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/29 16:04:26 by sganon            #+#    #+#             */
/*   Updated: 2016/05/12 17:04:53 by sganon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	stock_cam_coord(char *str, int step, t_objs *obj)
{
	if (step > 5)
		ft_error("Too much coordinate for camera: expected 3", 2);
	if (step == 0)
		obj->x = ft_atof(str);
	if (step == 1)
		obj->y = ft_atof(str);
	if (step == 2)
		obj->z = ft_atof(str);
	if (step == 3)
		obj->rx = ft_atof(str);
	if (step == 4)
		obj->ry = ft_atof(str);
	if (step == 5)
		obj->rz = ft_atof(str);
}

void		check_format(char *str, int i)
{
	while (str[i] && str[i] != ')')
	{
		if (!ft_isdigit(str[i]) && !ft_isspace(str[i]) && str[i] != ','
				&& str[i] != '-' && str[i] != '.')
		{
			ft_error("Bad character for camera/object/light description.", 2);
		}
		if (str[i] == '\n')
			ft_error("')' expected for camera/object/light coordinate", 2);
		i++;
	}
}

static void	check_cam_coord(char *str, int i, t_objs *obj)
{
	int		tmp;
	char	buffer[256];
	int		step;

	tmp = 0;
	step = 0;
	check_format(str, i);
	while (str[++i] != '\n')
	{
		if (str[i] == ',' || str[i] == ')')
		{
			stock_cam_coord(buffer, step, obj);
			ft_bzero(buffer, 256);
			if (str[i] == ')')
				break ;
			tmp = 0;
			step++;
			i++;
		}
		if (tmp > 256)
			ft_error("Coordinate is too big.", 2);
		buffer[tmp] = str[i];
		tmp++;
	}
}

int			get_camera(char *str, t_objs *obj)
{
	char	*cam_start;
	int		i;

	if (!(cam_start = ft_strstr(str, "camera")))
		return (0);
	i = 6;
	obj->id = 0;
	while (ft_isspace(cam_start[i]))
		i++;
	if (cam_start[i] == '(')
		check_cam_coord(cam_start, (i + 1), obj);
	else
		ft_error("'(' expected for camera coordinate", 2);
	return (1);
}
