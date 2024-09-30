/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_spheres.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 12:56:52 by jcummins          #+#    #+#             */
/*   Updated: 2024/09/30 16:10:12 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

//	there was a bug with the line
//	temp_t = (eq.b + sqrt(eq.discriminant)) / (2 * eq.a);
//	because we need the negative square root - positive root
//	results in rendering the far side of the sphere.
t_color	intersect_sphere(t_sphere *sphere, t_ray *ray, float *t)
{
	float		temp_t;
	t_quadratic	eq;
	t_vec3		oc;	//	points from cam origin to the sphere center

	vec3_a_to_b(oc, *ray->origin, sphere->center);
	eq.a = dot_product(ray->udir, ray->udir);
	eq.b = 2 * dot_product(oc, ray->udir);
	eq.c = dot_product(oc, oc) - (sphere->radius * sphere->radius);
	eq.discriminant = eq.b * eq.b - 4 * eq.a * eq.c;
	if (eq.discriminant < 0)
		return (-1);
	temp_t = (eq.b - sqrt(eq.discriminant)) / (2 * eq.a);
	if (temp_t > 0.001 && temp_t < *t)
	{
		*t = temp_t;
		return (sphere->color);
	}
	return (-1);
}

t_color	intersect_spheres(t_scene *scene, t_ray *ray, float *t)
{
	t_color	temp_color;
	t_color	pixel_color;
	float	temp_t;
	int		i;

	i = -1;
	temp_color = -1;
	pixel_color = -1;
	temp_t = *t;
	while (++i < scene->n_spheres)
	{
		temp_color = intersect_sphere(&scene->sphs[i], ray, &temp_t);
		if (scene->selected && &scene->sphs[i] == scene->selected)
		{
			temp_color = 0xFFFFFF;
		}
		if ((temp_color >= 0) && temp_t < *t)
		{
			pixel_color = temp_color;
			if (ray->origin == &scene->cam.point)
			{
				scene->screen_object[ray->y][ray->x] = &scene->sphs[i];
				scene->select_type[ray->y][ray->x] = SEL_SPHERE;
			}
			*t = temp_t;
		}
		temp_color = -1;
	}
	return (pixel_color);
}
