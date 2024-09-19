/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 10:05:20 by jcummins          #+#    #+#             */
/*   Updated: 2024/09/19 19:18:38 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

#include "miniRT.h"

typedef float	t_vector[3];
typedef int		t_color;

typedef struct	s_ambient
{
	bool		lock;
	float		lum;
	t_color		hue;
}				t_ambient;

typedef struct	s_camera
{
	bool		lock;
	t_vector	point;
	t_vector	dir;
	int			fov;
}				t_camera;

typedef struct	s_light
{
	bool		lock;
	t_vector	point;
	float		lum;
	t_color		hue;
}				t_light;

typedef struct	s_sphere
{
	t_vector	center;
	float		diamtr;
	int			id;
	t_color		color;
}				t_sphere;

typedef struct	s_plane
{
	t_vector	anch;
	t_vector	norm;
	int			id;
	t_color		color;
}				t_plane;

typedef struct	s_cylinder
{
	t_vector	center;
	t_vector	axis;
	float		diamtr;
	float		height;
	int			id;
	t_color		color;
}				t_cylinder;

typedef struct	s_scene
{
	char		*fname;
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

#endif
