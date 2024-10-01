/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_light_ray.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 15:33:38 by jcummins          #+#    #+#             */
/*   Updated: 2024/10/01 19:57:46 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_color	cast_light_ray(t_scene *scene, t_ray *ray, float *light_t)
{
	float	temp_t;
	t_color	light_color;

	temp_t = INFINITY;
	intersect_planes(scene, ray, &temp_t);
	if (temp_t < *light_t)
		return (0);
	intersect_spheres(scene, ray, &temp_t);
	if (temp_t < *light_t)
		return (0);
	light_color = scene->light.hue;
	light_color = color_shift(light_color, 0x000000, 1 - scene->light.lum);
	return (light_color);
}

t_color	prep_light_ray(t_scene *scene, t_vec3 bounce_point)
{
	float		light_t;
	t_color		light_color;
	t_ray		ray;

	light_t = INFINITY;
	vec3_set_a(ray.bounce, bounce_point);
	ray.origin = &ray.bounce;
	vec3_a_to_b(ray.dir, bounce_point, scene->light.point);
	vec3_normalize(ray.udir, ray.dir);
	light_t = vec3_length(ray.dir);
	light_color = cast_light_ray(scene, &ray, &light_t);
	if (light_color > 0)
		light_color = shade_pixel_distance(light_color, light_t);
	return (light_color);
}
