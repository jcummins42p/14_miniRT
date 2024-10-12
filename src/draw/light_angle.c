/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_angle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 20:45:33 by jcummins          #+#    #+#             */
/*   Updated: 2024/10/12 16:04:50 by akretov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void vec3_scale_add(t_vec3 dest, t_vec3 base, t_vec3 direction, float magnitude)
{
	// Scale the direction vector by the given magnitude
	t_vec3 scaled_direction;
	vec3_scaleize(scaled_direction, direction, magnitude);

	// Add the scaled direction to the base vector
	dest[_X] = base[_X] + scaled_direction[_X];
	dest[_Y] = base[_Y] + scaled_direction[_Y];
	dest[_Z] = base[_Z] + scaled_direction[_Z];
}

t_color light_angle_cylinder(t_scene *scene, t_ray *ray, int light_color)
{
	t_cylinder	*cylinder;
	float		dot_prod;
	t_vec3		light;
	t_vec3		point_on_axis;
	t_vec3		normal;

	cylinder = (t_cylinder *)ray->object;

	// Calculate the projection of the intersection point onto the cylinder's axis
	t_vec3 intersection_to_center;
	vec3_a_to_b(intersection_to_center, cylinder->center, ray->bounce);
	float projection_length = dot_product(intersection_to_center, cylinder->axis);

	// Calculate the closest point on the cylinder's axis to the intersection point
	vec3_scale_add(point_on_axis, cylinder->center, cylinder->axis, projection_length);

	// Calculate the normal vector at the intersection point on the cylinder's surface
	vec3_a_to_b(normal, point_on_axis, ray->bounce);
	vec3_normalize(normal, normal);

	// Adjust the normal direction based on the ray direction
	dot_prod = dot_product(ray->udir, normal);
	if (dot_prod > 0)
		vec3_invert(normal);

	// Calculate the light vector
	vec3_a_to_b(light, scene->light.point, ray->bounce);
	vec3_normalize(light, light);

	// Calculate the dot product of the light direction and the normal
	dot_prod = dot_product(light, normal);
	if (dot_prod > 0)
		return (XCOL_BLK);

	return (color_shift(XCOL_BLK, light_color, (log((0 - dot_prod) * 10)) + 0.1));
}


t_color	light_angle_plane(t_scene *scene, t_ray *ray, int light_color)
{
	t_plane		*plane;
	float		dot_prod;
	t_vec3		light;

	plane = (t_plane *)ray->object;
	dot_prod = dot_product(ray->udir, plane->norm);
	if (dot_prod > 0)
		vec3_invert(plane->norm);
	vec3_a_to_b(light, scene->light.point, ray->bounce);
	vec3_normalize(light, light);
	dot_prod = dot_product(light, plane->norm);
	if (dot_prod > 0)
		return (XCOL_BLK);
	return (color_shift(XCOL_BLK, light_color, (log((0 - dot_prod) * 10)) + 0.1));
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
	if (ray->object_type == SEL_CYLINDER_SIDE)
		return (light_angle_cylinder(scene, ray, light_color));
	if (ray->object_type == SEL_CYLINDER_CAP)
		return (light_angle_plane(scene, ray, light_color));
	else
		return (light_color);
}
