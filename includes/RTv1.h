/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RTv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/18 18:12:14 by sganon            #+#    #+#             */
/*   Updated: 2016/04/18 20:00:07 by sganon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H
# include "libft.h"
# include "../mlx/mlx.h"
# include <math.h>

# define WIN_X	1920
# define WIN_Y	1080

# define ESC	53

typedef unsigned char	t_bytes;

typedef struct			s_rgb
{
	t_bytes				r;
	t_bytes				g;
	t_bytes				b;
}						t_rgb;

typedef struct			s_color
{
	int					color;
	t_rgb				rgb;
}						t_color;

typedef struct			s_env
{
	void				*mlx;
	void				*win;
	double				*cos;
	double				*sin;
	double				*tan;
	void				*img_ptr;
	char				*img;
	int					bpp;
	int					sl;
	int					end;
}						t_env;

int						init_env(t_env *e);
int						create_image(t_env *e);
int						key_events(int key, t_env *e);

# endif
