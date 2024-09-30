/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_light.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:24:48 by jcummins          #+#    #+#             */
/*   Updated: 2024/09/29 10:54:27 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

//	allocates value magnitude t to float pointer if direction vector is aligned
//	with unit vector, and returns 0 if t is a valid solution.
int	get_t(t_vec3 dir_vec, t_vec3 unit_vec, float *t)
{
	t_vec3	t;
	int		dimension;

	dimension = -1;
	zero_vector(t);
	while (++dimension < 3)
	{
		if (dir_vec[dimension] > EPSILON && unit_vec[dimension] > EPSILON)
			t[dimension] = (dir_vec[dimension] / unit_vec[dimension]);
	}
	dimension = -1;
	while (++dimension < 3)

}

//	the dot (or scalar) product of two parallel vectors equals the product of
//	their magnitudes.
//	We know the unit vector of the camera ray and full euclidean from camera
//	to light.
//	C (camera position) - position vector
//	R (ray direction) - unit vector
//	L (light position) - position vector
//	t = time
//	t = (L - C) / R
//	for point L to lie on ray R, t must be positive (in front of the camera)
//	A single solution t must exist for all components of the direction vector
//	L - C = cam_to_light direction vector
//	so t = cam_to_light direction vector / ray unit vector
t_color	intersect_light(t_light *light, t_ray *ray, float *t)
{
	float		temp_t;
	t_vec3		cam_to_light;
	float		denominator;

	denominator = dot_product(ray->udir, plane->norm);
	if (fl_abs(denominator) > EPSILON)
	{
		vec3_a_to_b(cam_to_anch, *ray->origin, plane->anch);
		temp_t = dot_product(cam_to_anch, plane->norm) / (denominator);
		if (temp_t > 0.001 && temp_t < *t)
		{
			*t = temp_t;
			return (plane->color);
		}
	}
	return (-1);
}

//	currently this function is redundant since we only have one light source
//	but it will be useful when there are multiple
t_color	intersect_planes(t_scene *scene, t_ray *ray, float *t)
{
	t_color	temp_color;
	t_color	pixel_color;
	float	temp_t;
	int		i;

	i = -1;
	temp_color = -1;
	pixel_color = -1;
	temp_t = *t;
	while (++i < scene->n_planes)
	{
		temp_color = intersect_plane(&scene->plns[i], ray, &temp_t);
		if ((temp_color >= 0) && temp_t < *t)
		{
			pixel_color = temp_color;
			*t = temp_t;
		}
		temp_color = -1;
	}
	return (pixel_color);
}
