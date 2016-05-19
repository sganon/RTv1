/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/04 18:04:01 by sganon            #+#    #+#             */
/*   Updated: 2016/05/05 18:33:57 by sganon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void		stock_light_coord(char *str, t_light *light, int step)
{
	if (step == 0)
		light->x = ft_atoi(str);
	if (step == 1)
		light->y = ft_atoi(str);
	if (step == 2)
		light->z = ft_atoi(str);
	if (step > 2)
		ft_error("Too much coordinate for light: expected 3", 2);
}

char 		*find_first_light(char *str)
{
	str = ft_strstr(str, "light");
	if (!str)
		return (NULL);
	else
		return (str);
}

void		get_light_coord(char *str, t_env *e)
{
	int		i;
	int		step;
	char	buffer[256];
	int		tmp;

	i = 5;
	while(ft_isspace(str[i]))
		i++;
	if (str[i] == '(')
	{
		i++;
		check_format(str, i);
		tmp = 0;
		step = 0;
		while(str[i] != '\n')
		{
			if(str[i] == ',' || str[i] == ')')
			{
				stock_light_coord(buffer, e->light, step);
				ft_bzero(buffer, 256);
				if (str[i] == ')')
					break;
				tmp = 0;
				i++;
				step++;
			}			
			if (tmp <= 255)
				buffer[tmp] = str[i];
			tmp++;
			i++;
		}
	}
	else
		ft_error("'(' expected for light coordinate", 2);
}

void		get_light(char *str, t_env *e)
{
	if (!(str = ft_strstr(str, "light")))
		ft_error("No light description found. Please add at least one", 2);
	get_light_coord(str, e);
	str = ft_trim(str);
	while((str = ft_strstr(str, "light")) != NULL)
	{
		e->light->next = (t_light *)malloc(sizeof(t_light));
		e->light = e->light->next;
		get_light_coord(str, e);
		str = ft_trim(str);
	}
	e->light->next = NULL;
	e->light = e->begin_light; 
}