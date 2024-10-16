/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 10:05:20 by jcummins          #+#    #+#             */
/*   Updated: 2024/10/16 17:13:53 by akretov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "miniRT.h"

typedef float	t_vec3[3];
typedef float	t_vec2[2];
typedef int		t_rgb[3];
typedef int		t_pixel[2];


typedef struct s_quaternion
{
    float w;   // Real part
    float x;   // i component
    float y;   // j component
    float z;   // k component
} t_quaternion;



typedef union u_col
{
	char		c[3];
	int			i;
}				t_col;

typedef struct s_quadratic
{
	float		discriminant;
	float		a;
	float		b;
	float		c;
}				t_quadratic;

typedef struct s_ray
{
	int			x;
	int			y;
	void		*object;
	int			object_type;
	t_vec3		*origin;
	t_vec3		bounce;
	t_vec3		dir;
	t_vec3		udir;
}				t_ray;

typedef struct s_ambient
{
	int			lock;
	float		lum;
	int		hue;
}				t_ambient;

typedef struct s_camera
{
	int			lock;
	t_vec3		point;
	t_vec3		dir;	//	unit vector pointing out of the camera
	t_vec3		right;	//	unit vector pointing up relative to the camera
	t_vec3		up;		//	unit vector pointing right relative to the camera
	t_vec3		point_def;
	t_vec3		dir_def;
	int			fov;
}				t_camera;

typedef struct s_light
{
	int			lock;
	t_vec3		point;
	float		lum;
	int		hue;
}				t_light;

typedef struct s_bbox
{
	t_vec3		min;
	t_vec3		max;
}				t_bbox;

typedef struct s_sphere
{
	t_bbox		bounds;
	t_vec3		center;
	float		diamtr;
	float		radius;
	int			id;
	int			color;
	int			shine;
}				t_sphere;

typedef struct s_plane
{
	t_bbox		bounds;
	t_vec3		anch;
	t_vec3		norm;
	int			id;
	int			color;
	int			shine;
}				t_plane;

typedef struct s_cylinder
{
	t_bbox		bounds;
	t_vec3		center;
	t_vec3		axis;
	float		diamtr;
	float		radius;
	float		height;
	int			id;
	int			color;
	int			shine;
}				t_cylinder;

typedef struct s_img
{
	void	*img;
	char 	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

typedef struct s_render
{
	int		res;
	bool	scan;
}				t_render;

typedef struct s_scene
{
	char		*fname;
	void		*screen_object[RES_H][RES_W];	//	each pixel stores the object in it
	int			select_type[RES_H][RES_W];
	t_pixel		light_point;
	void		*selected;
	int			sel_type;
	t_img		*img;
	t_render	rend;
	t_ambient	amb;
	t_camera	cam;
	t_camera	cam_defaults;
	t_light		light;
	t_sphere	*sphs;
	t_plane		*plns;
	t_cylinder	*cyls;
	t_vec3		project;	//	used as 2d coordinates of projection plane
	int			id;
	int			n_cylinders;
	int			n_planes;
	int			n_spheres;
	int			sky;
	t_mutex		mutex;
	bool		valid;
}				t_scene;

typedef struct s_rt
{
	t_scene	**scenes;
	int		*fd;
	int		curr_scene;
	int		n_scenes;
	int		errcode;
}				t_rt;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	t_rt	*rt;
	float	aspect_ratio;
	int		y;
	t_mutex	mutex;
	bool	multithread;
}				t_mlx;

typedef struct s_render_queue
{
	t_mlx	*mlx;
	int		y;
}				t_render_queue;

#endif
