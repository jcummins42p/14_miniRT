/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 10:05:20 by jcummins          #+#    #+#             */
/*   Updated: 2024/09/23 18:46:27 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "miniRT.h"

typedef float	t_vector[3];
typedef int		t_color;

typedef struct s_ray
{
	t_vector	*origin;
	t_vector	*dir;
	t_vector	*udir;
}				t_ray;

typedef struct s_ambient
{
	int			lock;
	float		lum;
	t_color		hue;
}				t_ambient;

typedef struct s_camera
{
	int			lock;
	t_vector	point;
	t_vector	dir;
	int			fov;
}				t_camera;

typedef struct s_light
{
	int			lock;
	t_vector	point;
	float		lum;
	t_color		hue;
}				t_light;

typedef struct s_bbox
{
	t_vector	min;
	t_vector	max;
}				t_bbox;

typedef struct s_sphere
{
	t_bbox		bounds;
	t_vector	center;
	float		diamtr;
	int			id;
	t_color		color;
}				t_sphere;

typedef struct s_plane
{
	t_bbox		bounds;
	t_vector	anch;
	t_vector	norm;
	int			id;
	t_color		color;
}				t_plane;

typedef struct s_cylinder
{
	t_bbox		bounds;
	t_vector	center;
	t_vector	axis;
	float		diamtr;
	float		height;
	int			id;
	t_color		color;
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
	t_img		*img;
	t_render	rend;
	t_ambient	amb;
	t_camera	cam;
	t_light		light;
	t_sphere	*sphs;
	t_plane		*plns;
	t_cylinder	*cyls;
	int			id;
	int			n_cylinders;
	int			n_planes;
	int			n_spheres;
	t_color		sky;
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
}				t_mlx;

#endif
