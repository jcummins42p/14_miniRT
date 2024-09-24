/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_planes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:24:48 by jcummins          #+#    #+#             */
/*   Updated: 2024/09/24 20:37:05 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_color	intersect_plane(t_plane *plane, t_ray *ray, float *t)
{
	t_vec3		p0l0;	//	points from cam origin to a known point on the plane
	float		denom;

	denom = dot_product(ray->dir, plane->norm);
	if (fl_abs(denom) < 0.2)
		return (-1);
	p0l0[_X] = plane->anch[_X] - (*ray->origin)[_X];
	p0l0[_Y] = plane->anch[_Y] - (*ray->origin)[_Y];
	p0l0[_Z] = plane->anch[_Z] - (*ray->origin)[_Z];
	*t = dot_product(p0l0, plane->norm) / denom;
	return (plane->color);
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
