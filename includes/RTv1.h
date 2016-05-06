/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RTv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/18 18:12:14 by sganon            #+#    #+#             */
/*   Updated: 2016/05/06 13:58:14 by sganon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H
# include "libft.h"
# include "../mlx/mlx.h"
# include <math.h>

# define WIN_X	1000
# define WIN_Y	1000
# define FOV	66

# define SPH	6
# define CYL	8
# define CON	4
# define PLA	5

# define INT_MAX	2147483647 

# define ESC	53

# define SQR(x)	(x * x)

typedef unsigned char	t_bytes;

typedef struct			s_rgb
{
	t_bytes				r;
	t_bytes				g;
	t_bytes				b;
}						t_rgb;

typedef union			u_color
{
	size_t				color;
	t_rgb				rgb;
}						t_color;

typedef struct			s_cam
{
	double				x;
	double				y;
	double				z;
	double				rx;
	double				ry;
	double				rz;
}						t_cam;

typedef struct			s_vector
{
	double				x;
	double				y;
	double				z;
}						t_vector;

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
	double				x;
	double				y;
	double				z;
	double				rx;
	double				ry;
	double				rz;
	int					rayon;
	int					color;
	double				s1;
	double				s2;
	struct s_objs 		*next;
}						t_objs;

typedef struct			s_env
{
	void				*mlx;
	void				*win;
	double				*cos;
	double				*sin;
	double				*tan;
	double				last_draw;
	void				*img_ptr;
	char				*img;
	int					bpp;
	int					sl;
	double				a;
	double				b;
	double				c;
	int					end;
	t_cam				cam;
	t_vector			vector;
	t_vector			light;
	t_objs				*begin_list;
}						t_env;

int						init_env(t_env *e);
int						create_image(t_env *e);
int						key_events(int key, t_env *e);
int						get_camera(char *str, t_objs *obj);
void					check_format(char *str, int i);
void					parse_coord(char *str, int step, t_objs *obj);
void					cast(t_env *e, t_objs *obj);
void					get_intersect(t_objs *obj, t_env *e, int x, int y);
void					plane_intersect(t_objs *obj, t_env *e, int x, int y);
void					get_light(char *str, t_env *e);
void					draw_in_img(t_env *e, int x, int y, double cosi);
t_objs					*get_obj(char *str, t_objs *obj);
t_objs					*parsing(char *filename, t_env *e, t_objs *obj);
t_vector				normalize_vector(t_vector vector);
t_vector				vector_double(t_vector v);
t_vector				new_vector(t_vector v1, t_vector v2);
t_vector				rotate_vector(t_vector vector, t_env *e);
double					vector_scalar(t_vector v1, t_vector v2);

# endif
