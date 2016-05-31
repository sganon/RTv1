/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/19 15:48:24 by sganon            #+#    #+#             */
/*   Updated: 2016/05/12 16:06:39 by sganon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

#include <stdio.h>

t_objs		*get_data(char *str, t_objs *obj, t_env *e)
{
	if (!(get_camera(str, obj)))
		ft_error("Camera description not found. Please add one", 2);
	if (!(obj = get_obj(str, obj)))
		ft_error("No object description found. Please add one", 2);
	get_light(str, e);
	free(str);
	return (obj);
}

t_objs		*parsing(char *filename, t_env *e, t_objs *obj)
{
	int		fd;
	char	*str;
	char	*tmp;
	int		ret;

	if ((fd = open(filename, O_RDONLY)) < 3)
		ft_error("Cannot open file", 2);
	tmp = ft_strnew(1);
	while (42)
	{
		ret = get_next_line(fd, &str);
		if (ret != 1)
			break ;
		tmp = ft_strjoin(tmp, str);
		tmp = ft_strjoin(tmp, "\n");
		free(str);
	}
	if (ret == -1)
		return (NULL);
	return (get_data(tmp, obj, e));
}
