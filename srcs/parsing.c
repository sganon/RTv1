/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/19 15:48:24 by sganon            #+#    #+#             */
/*   Updated: 2016/04/29 16:16:00 by sganon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

#include <stdio.h>
int		get_obj(char *str, t_objs *obj)
{
	if (!(get_camera(str, obj)))
		ft_error("Camera description not found.", 2);
	obj->next = (t_objs *)malloc(sizeof(t_objs));
	//obj = obj->next;
	return (1);
}

int		parsing(char *filename, t_env *e, t_objs *obj)
{
	int		fd;
	char	*str;
	char	*tmp;
	int		ret;

	(void)obj;
	(void)e;
	if ((fd = open(filename, O_RDONLY)) < 3)
		return (0);
	tmp = ft_strnew(0);
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
	get_obj(tmp, obj);
	ft_putendl(tmp);
	return (1);
}
