/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/19 15:48:24 by sganon            #+#    #+#             */
/*   Updated: 2016/04/29 18:47:37 by sganon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

#include <stdio.h>

int		get_obj_type(char *str)
{
	if (str[0] == 's')
		return (6);
	if (str[0] == 'c' && str[1] == 'y')
		return (8);
	if (str[0] == 'c' && str[0] == 'o')
		return (4);
	if (str[0] == 'p')
		return (5);
	else
		return (0);
}


void	get_coord(char *str, int i, t_objs *obj)
{
	(void)obj;
	check_format(str, i);
	while (str[i] != '\n')
	{
		i++;
	}
}

void	get_obj_coord(char *str, t_objs *obj)
{
	int	i;

	obj->next = (t_objs *)malloc(sizeof(t_objs));
	obj = obj->next;
	i = get_obj_type(str);
	obj->id = i;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '(')
		get_coord(str, i + 1, obj);
	else
		ft_error("'(' expected for object coordinate", 2);
}

char	*find_first_obj(char *str)
{
	int i;
	int	min_i;

	i = 0;
	min_i = ft_strlen(str);
	while (str[i])
	{
		if (str[i] == 's' && &str[i] == ft_strstr(str, "sphere"))
			min_i = i < min_i ? i : min_i;
		if (str[i] == 'c' && &str[i] == ft_strstr(str, "cylinder"))
			min_i = i < min_i ? i : min_i;
		if (str[i] == 'c' && &str[i] == ft_strstr(str, "cone"))
			min_i = i < min_i ? i : min_i;
		if (str[i] == 'p' && &str[i] == ft_strstr(str, "plane"))
			min_i = i < min_i ? i : min_i;
		i++;
	}
	return (&str[min_i]);
}

int		get_obj(char *str, t_objs *obj)
{
	char	*obj_start;
	
	obj_start = find_first_obj(str);
	get_obj_coord(obj_start, obj);
	ft_putendl(obj_start);
	return (1);
}

int		get_data(char *str, t_objs *obj)
{
	if (!(get_camera(str, obj)))
		ft_error("Camera description not found. Please add one", 2);
	if (!get_obj(str, obj))
		ft_error("No object description found. Please add one", 2);
	return (1);
}

int		parsing(char *filename, t_env *e, t_objs *obj)
{
	int		fd;
	char	*str;
	char	*tmp;
	int		ret;

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
	get_data(tmp, obj);
	ft_putendl(tmp);
	return (1);
}
