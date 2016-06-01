/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/18 18:26:33 by sganon            #+#    #+#             */
/*   Updated: 2016/04/18 18:29:53 by sganon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		key_events(int key, t_env *e)
{
	if (key == ESC)
		exit(0);
	if (key == W_KEY)
		e->cam.z += 1;
	if (key == S_KEY)
		e->cam.z -= 1;
	if (key == A_KEY)
		e->cam.x -= 1;
	if (key == D_KEY)
		e->cam.x += 1;
	if (key == UP_KEY)
		e->cam.y += 1;
	if (key == DOWN_KEY)
		e->cam.y -= 1;
	if (key == Q_KEY && (e->cam.rx * 100 + 2) < 36000.0)
		e->cam.ry += 2;
	if (key == E_KEY && (e->cam.rx * 100 - 2) > -29999.0)
		e->cam.ry -= 2;
	expose_hook(e);
	return (1);
}
