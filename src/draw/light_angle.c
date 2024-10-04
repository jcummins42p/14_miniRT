/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_angle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 20:45:33 by jcummins          #+#    #+#             */
/*   Updated: 2024/10/04 10:07:30 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_color	light_angle_plane(t_scene *scene, t_ray *ray, int light_color)
{
	t_plane		*plane;
	float		dot_prod;
	t_vec3		light;

	plane = (t_plane *)ray->object;
	dot_prod = dot_product(ray->udir, plane->norm);
	if (dot_prod > 0)
		vec3_invert(plane->norm);
	plane = (t_plane *)ray->object;
	vec3_a_to_b(light, scene->light.point, ray->bounce);
	vec3_normalize(light, light);
	dot_prod = dot_product(light, plane->norm);
	if (dot_prod > 0)
		return (XCOL_BLK);
	return (color_shift(light_color, XCOL_BLK, (dot_prod)));
}

t_color	light_angle_sphere(t_scene *scene, t_ray *ray, int light_color)
{
	t_sphere	*sphere;
	float		dot_prod;
	t_vec3		normal;
	t_vec3		light;

	sphere = (t_sphere *)ray->object;
	vec3_a_to_b(normal, sphere->center, ray->bounce);
	vec3_a_to_b(light, scene->light.point, ray->bounce);
	vec3_normalize(light, light);
	vec3_normalize(normal, normal);
	dot_prod = dot_product(light, normal);
	if (dot_prod > 0)
		return (XCOL_BLK);
	return (color_shift(XCOL_BLK, light_color, (0 - (dot_prod))));
}

t_color light_angle(t_scene *scene, t_ray *ray, int light_color)
{
	if (ray->object_type == SEL_SPHERE)
		return (light_angle_sphere(scene, ray, light_color));
	//	planes not working yet
	if (ray->object_type == SEL_PLANE)
		return (light_angle_plane(scene, ray, light_color));
	else
		return (light_color);
}
