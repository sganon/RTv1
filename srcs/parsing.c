/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/19 15:48:24 by sganon            #+#    #+#             */
/*   Updated: 2016/05/03 18:41:05 by sganon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

#include <stdio.h>

t_objs		*get_data(char *str, t_objs *obj)
{
	if (!(get_camera(str, obj)))
		ft_error("Camera description not found. Please add one", 2);
	if (!(obj = get_obj(str, obj)))
		ft_error("No object description found. Please add one", 2);
	return (obj);
}

t_objs		*parsing(char *filename, t_env *e, t_objs *obj)
{
	int		fd;
	char	*str;
	char	*tmp;
	int		ret;

	(void)e;
	if ((fd = open(filename, O_RDONLY)) < 3)
		return (0);
	tmp = ft_strnew(1);
	while (42)
	{
		ret = get_next_line(fd, &str);
		if (ret != 1)
			break ;
		tmp = ft_strjoin(tmp, str);
		tmp = ft_strjoin(tmp, "\n");
	}
	if (ret == -1)
		return (0);
	ft_putendl(tmp);
	return (get_data(tmp, obj));
}
