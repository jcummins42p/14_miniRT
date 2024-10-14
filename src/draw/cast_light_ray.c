/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_light_ray.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 15:33:38 by jcummins          #+#    #+#             */
/*   Updated: 2024/10/14 19:15:31 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

//	this is where calculations for light direction vs normal direction need to go
int	cast_light_ray(t_scene *scene, t_ray *ray, float *light_t)
{
	float	temp_t;
	int	light_color;

	temp_t = INFINITY;
	intersect_planes(scene, ray, &temp_t);
	if ((temp_t + EPSILON) < *light_t)
		return (0);
	intersect_spheres(scene, ray, &temp_t);
	if ((temp_t + EPSILON) < *light_t)
		return (0);
	intersect_cylinders(scene, ray, &temp_t);
	if ((temp_t + EPSILON) < *light_t)
		return (0);
	light_color = scene->light.hue;
	return (light_color);
}

int	prep_light_ray(t_scene *scene, t_vec3 bounce_point)
{
	float		light_t;
	int		light_color;
	t_ray		ray;

	light_t = INFINITY;
	vec3_set_a(ray.bounce, bounce_point);
	ray.origin = &ray.bounce;
	vec3_a_to_b(ray.dir, bounce_point, scene->light.point);
	vec3_normalize(ray.udir, ray.dir);
	light_t = vec3_length(ray.dir);
	light_color = cast_light_ray(scene, &ray, &light_t);
	if (light_color > 0)
		light_color = shade_light_distance(light_color, light_t, scene->light.lum);
	return (light_color);
}
