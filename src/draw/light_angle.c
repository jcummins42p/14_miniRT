/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_angle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 20:45:33 by jcummins          #+#    #+#             */
/*   Updated: 2024/10/17 11:16:40 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

float light_angle_cylinder(t_scene *scene, t_ray *ray)
{
	float		dot_prod;
	t_vec3		light;
	t_vec3		normal;

	get_cylinder_normal(normal, (t_cylinder *)ray->object, ray);
	dot_prod = dot_product(ray->udir, normal);
	if (dot_prod > 0)
		vec3_invert(normal);
	vec3_a_to_b(light, scene->light.point, ray->bounce);
	vec3_normalize(light, light);
	return (dot_product(light, normal));
}

float	light_angle_cyltop(t_scene *scene, t_ray *ray)
{
	t_vec3		light;
	t_vec3		normal;

	vec3_set_a(normal, ((t_cylinder *)ray->object)->axis);
	if (dot_product(ray->udir, normal) > 0)
		vec3_invert(normal);
	vec3_a_to_b(light, scene->light.point, ray->bounce);
	vec3_normalize(light, light);
	return (dot_product(light, normal) * 10);
}

float	light_angle_plane(t_scene *scene, t_ray *ray)
{
	t_plane		*plane;
	t_vec3		light;

	plane = (t_plane *)ray->object;
	if (dot_product(ray->udir, plane->norm) > 0)
		vec3_invert(plane->norm);
	vec3_a_to_b(light, scene->light.point, ray->bounce);
	vec3_normalize(light, light);
	return ((dot_product(light, plane->norm) * 10));
}

float	light_angle_sphere(t_scene *scene, t_ray *ray)
{
	t_sphere	*sphere;
	t_vec3		normal;
	t_vec3		light;

	sphere = (t_sphere *)ray->object;
	vec3_a_to_b(normal, sphere->center, ray->bounce);
	vec3_a_to_b(light, scene->light.point, ray->bounce);
	vec3_normalize(light, light);
	vec3_normalize(normal, normal);
	return (dot_product(light, normal));
}

int	light_angle(t_scene *scene, t_ray *ray, int light_color)
{
	float	light_angle;

	if (light_color < 0)
		return (-1);
	if (ray->object_type == SEL_SPHERE)
		light_angle = light_angle_sphere(scene, ray);
	else if (ray->object_type == SEL_PLANE)
		light_angle = light_angle_plane(scene, ray);
	else if (ray->object_type == SEL_CYLINDER_SIDE)
		light_angle = light_angle_cylinder(scene, ray);
	else if (ray->object_type == SEL_CYLINDER_CAP)
		light_angle = light_angle_cyltop(scene, ray);
	else
		light_angle = 1;
	if (light_angle > 0)
		return (-1);
	else
		return (color_shift(XCOL_BLK, light_color, (0 - light_angle)));
}
