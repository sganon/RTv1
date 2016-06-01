/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/19 15:48:24 by sganon            #+#    #+#             */
/*   Updated: 2016/05/12 16:21:05 by sganon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	get_coord(char *str, int i, t_objs *obj)
{
	char	buffer[256];
	int		tmp;
	int		step;

	check_format(str, i);
	tmp = 0;
	step = 0;
	while (str[i] != '\n')
	{
		if (str[i] == ',' || str[i] == ')')
		{
			parse_coord(buffer, step, obj);
			ft_bzero(buffer, 256);
			if (str[i] == ')')
				break ;
			step++;
			tmp = 0;
			i++;
		}
		if (tmp > 255)
			ft_error("Coordinate is too big.", 2);
		buffer[tmp] = str[i];
		tmp++;
		i++;
	}
}

static void	get_obj_coord(char *str, t_objs *obj)
{
	int	i;

	i = get_obj_type(str);
	obj->id = i;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '(')
		get_coord(str, i + 1, obj);
	else
		ft_error("'(' expected for object coordinate", 2);
}

static char	*find_first_obj(char *str)
{
	unsigned int	i;
	unsigned int	min_i;

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
	if (min_i == ft_strlen(str))
		return (NULL);
	return (&str[min_i]);
}

char		*ft_trim(char *str)
{
	char	*new;
	int		i;

	i = 0;
	if (!str)
		return (str);
	while (str[i] != '\n')
		i++;
	new = ft_strsub(str, i, ft_strlen(str));
	return (new);
}

t_objs		*get_obj(char *str, t_objs *obj)
{
	t_objs	*begin;

	begin = obj;
	while ((str = find_first_obj(str)) != NULL)
	{
		obj->next = (t_objs *)malloc(sizeof(t_objs));
		obj = obj->next;
		get_obj_coord(str, obj);
		str = ft_trim(str);
	}
	obj->next = NULL;
	return (begin);
}
