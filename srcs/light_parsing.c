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

void		stock_light_coord(char *str, t_env *e)
{
	static int	step = 0;

	if (step == 0)
		e->light.x = ft_atoi(str);
	if (step == 1)
		e->light.y = ft_atoi(str);
	if (step == 2)
		e->light.z = ft_atoi(str);
	if (step > 2)
		ft_error("Too much coordinate for light: expected 3", 2);
	step++;
}

void		get_light(char *str, t_env *e)
{
	char	*light;
	int		i;
	char	buffer[256];
	int		tmp;

	light = ft_strstr(str, "light");
	if (!light)
		ft_error("No light description found. Please add one", 2);
	i = 5;
	while (ft_isspace(light[i]))
		i++;
	if (light[i] == '(')
	{
		i++;
		check_format(light, i);
		tmp = 0;
		while (light[i] != '\n')
		{
			if (light[i] == ',' || light[i] == ')')
			{
				stock_light_coord(buffer, e);
				ft_bzero(buffer, 256);
				if (light[i] == ')')
					break;
				tmp = 0;
				i++;
			}
			if (tmp <= 255)
				buffer[tmp] = light[i];
			tmp++;
			i++;
		}
	}
}
