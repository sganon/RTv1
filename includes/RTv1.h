/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RTv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/18 18:12:14 by sganon            #+#    #+#             */
/*   Updated: 2016/04/29 18:44:02 by sganon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H
# include "libft.h"
# include "../mlx/mlx.h"
# include <math.h>

# define WIN_X	680
# define WIN_Y	480

# define ESC	53

typedef unsigned char	t_bytes;

typedef struct			s_rgb
{
	t_bytes				b;
	t_bytes				g;
	t_bytes				r;
}						t_rgb;

typedef struct			s_color
{
	int					color;
	t_rgb				rgb;
}						t_color;

typedef struct			s_pos
{
	double				x;
	double				y;
	double				z;
}						t_pos;

/* obj id :
 * 0 = camera;
 * 6 = sphere;
 * 5 = plan;
 * 4 = cone;
 * 8 = cylindre;
 */

/* obj color:
 * 0 = white
 * 1 = red
 * 2 = blue
 * 3 = green
 * 4 = yellow
 */

typedef struct			s_objs
{
	int					id;
	t_pos				pos_obj;
	int				rayon;
	int					color;
	struct s_objs 		*next;
}						t_objs;

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
t_objs						*parsing(char *filename, t_env *e, t_objs *obj);
int						get_camera(char *str, t_objs *obj);
void					check_format(char *str, int i);
void					parse_coord(char *str, int step, t_objs *obj);
t_objs					*get_obj(char *str, t_objs *obj);

# endif
