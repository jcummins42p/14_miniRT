/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_planes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:24:48 by jcummins          #+#    #+#             */
/*   Updated: 2024/09/27 15:21:09 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

//	the dot (or scalar) product of two vectors perpendicular to each other
//	always equals ZERO. a.b = ||a|| x ||b|| x cosΘ
//	if the ray is perpendicular with the plane it:
//		a) won't be hit by the ray and
//		b) would result in a division by 0 anyway
//			: so we need to exit at that point.
//
t_color	intersect_plane(t_plane *plane, t_ray *ray, float *t)
{
	float		temp_t;
	t_vec3		cam_to_anch;
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
