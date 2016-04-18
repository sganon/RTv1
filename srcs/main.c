/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/18 18:11:00 by sganon            #+#    #+#             */
/*   Updated: 2016/04/18 20:40:37 by sganon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void	white_img(t_env *e)
{
	int i;
	t_color	u;

	i = 0;
	u.color = 0xFFFFFF;
	while (i < WIN_Y * 20)
	{
		e->img[i] = u.rgb.r;
		e->img[i + 1] = u.rgb.g;
		e->img[i + 2] = u.rgb.b;
		ft_putnbr(e->img[i]);
		ft_putchar(' ');
		ft_putnbr(e->img[i + 1]);
		ft_putchar(' ');
		ft_putnbr(e->img[i + 2]);
		ft_putchar('\n');
		i += 3;
	}
}

int		expose_hook(t_env *e)
{
	if (!e->img_ptr)
		create_image(e);
	white_img(e);
	mlx_put_image_to_window(e->mlx, e->win, e->img_ptr, 0, 0);
	mlx_do_sync(e->mlx);
	return (1);
}

int		main(int argc, char **argv)
{
	t_env	*e;

	(void)argc;
	(void)argv;
	e = (t_env *)malloc(sizeof(t_env));
	if (!(init_env(e)))
		return(0);
	mlx_expose_hook(e->win, expose_hook, e);
	mlx_key_hook(e->win, key_events, e);
	mlx_loop(e->mlx);
	return (0);
}
