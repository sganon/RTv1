/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RTv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/18 18:12:14 by sganon            #+#    #+#             */
/*   Updated: 2016/05/11 17:14:53 by sganon           ###   ########.fr       */
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
	double				rx;
	double				ry;
	double				rz;
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
	int					sh;
	double				s1;
	double				s2;
	struct s_objs 		*next;
}						t_objs;

typedef struct			s_col
{
	double				s1;
	double				s2;
	t_objs				*obj;
}						t_col;

typedef struct 			s_light
{
	double				x;
	double				y;
	double				z;
	struct s_light		*next;
}						t_light;

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
	int					end;
	int					x;
	int					y;
	double				a;
	double				b;
	double				c;
	double				delta;
	t_cam				cam;
	t_vector			vector;
	t_cam				light_inter;
	t_vector			lvector;
	t_col				col;
	t_light				*light;
	t_light				*begin_light;
	t_objs				*begin_list;
}						t_env;

int						init_env(t_env *e);
int						create_image(t_env *e);
int						key_events(int key, t_env *e);
int						get_camera(char *str, t_objs *obj);
int						get_obj_type(char *str);
int						check_for_closer_obj(t_objs *obj, t_objs * tmp, t_env *e);
int						shadow(t_objs *obj, t_env *e);
char					*ft_trim(char *str);
void					plane_intersect(t_objs *obj, t_env *e, int shadow);
void					get_abc(t_env *e, t_objs *obj, int nb);
void					check_format(char *str, int i);
void					parse_coord(char *str, int step, t_objs *obj);
void					cast(t_env *e, t_objs *obj);
void					light_cast(t_env *e, t_objs *obj);
void					draw_in_img(t_env *e, double cosi, t_objs *obj);
void					get_light(char *str, t_env *e);
void					store_hit(t_objs *obj, t_env *e);
t_objs					*get_obj(char *str, t_objs *obj);
t_objs					*parsing(char *filename, t_env *e, t_objs *obj);
t_vector				normalize_vector(t_vector vector);
t_vector				new_vector(t_vector v1, t_vector v2);
t_vector				cam_object_vector(t_cam cam, t_objs *obj, t_env *e);
t_vector				cam_light_vector(t_cam cam, t_light *light);
t_vector				rotate_obj(t_vector vector, t_env *e, t_objs *obj);
t_vector				rotate_x(t_vector vector, t_env *e, double rot);
t_vector				rotate_y(t_vector vector, t_env *e, double rot);
t_vector				rotate_z(t_vector vector, t_env *e, double rot);
t_cam					rotate_cam(t_env *e);
double					vector_scalar(t_vector vect1, t_vector vect2);
double					specular_light(t_env *e, t_vector light, t_vector normal);
double					get_norme(t_objs *obj);

# endif
