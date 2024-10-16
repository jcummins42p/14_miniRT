/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specular.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 09:54:25 by jcummins          #+#    #+#             */
/*   Updated: 2024/10/16 17:41:31 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	specular_plane(t_scene *scene, t_ray *ray, int *pixel_color)
{
	t_plane		*plane;
	float		coincidence;
	t_vec3		light;
	t_vec3		reflect;

	plane = (t_plane *)ray->object;
	vec3_a_to_b(light, scene->light.point, ray->bounce);
	vec3_normalize(light, light);
	vec3_surface_reflection(reflect, light, plane->norm);
	coincidence = dot_product(ray->udir, reflect);
	if (coincidence < 0)
		return ;
	coincidence = (plane->shine / 100.0) * powf(coincidence, plane->shine);
	*pixel_color = color_shift(*pixel_color, scene->light.hue, coincidence);
}

void	specular_cyltop(t_scene *scene, t_ray *ray, int *pixel_color)
{
	t_cylinder	*cylinder;
	float		coincidence;
	t_vec3		light;
	t_vec3		reflect;

	cylinder = (t_cylinder *)ray->object;
	vec3_a_to_b(light, scene->light.point, ray->bounce);
	vec3_normalize(light, light);
	vec3_surface_reflection(reflect, light, cylinder->axis);
	coincidence = dot_product(ray->udir, reflect);
	if (coincidence < 0)
		return ;
	coincidence = (cylinder->shine / 100.0) * powf(coincidence, cylinder->shine);
	*pixel_color = color_shift(*pixel_color, scene->light.hue, coincidence);
}

void	specular_cylinder(t_scene *scene, t_ray *ray, int *pixel_color)
{
	t_cylinder	*cylinder;
	float		coincidence;
	t_vec3		normal;
	t_vec3		light;
	t_vec3		reflect;

	cylinder = (t_cylinder *)ray->object;
	get_cylinder_normal(normal, cylinder, ray);
	vec3_a_to_b(light, scene->light.point, ray->bounce);
	vec3_normalize(light, light);
	vec3_surface_reflection(reflect, light, normal);
	coincidence = dot_product(ray->udir, reflect);
	if (coincidence < 0)
		return ;
	coincidence = (cylinder->shine / 100.0) * powf(coincidence, cylinder->shine);
	*pixel_color = color_shift(*pixel_color, scene->light.hue, coincidence);
}

void	specular_sphere(t_scene *scene, t_ray *ray, int *pixel_color)
{
	t_sphere	*sphere;
	float		coincidence;
	t_vec3		normal;
	t_vec3		light;
	t_vec3		reflect;

	sphere = (t_sphere *)ray->object;
	vec3_a_to_b(normal, sphere->center, ray->bounce);
	vec3_a_to_b(light, scene->light.point, ray->bounce);
	vec3_normalize(light, light);
	vec3_normalize(normal, normal);
	vec3_surface_reflection(reflect, light, normal);
	coincidence = dot_product(ray->udir, reflect);
	if (coincidence < 0)
		return ;
	coincidence = (sphere->shine / 100.0) * powf(coincidence, sphere->shine);
	*pixel_color = color_shift(*pixel_color, scene->light.hue, coincidence);
}

void	specular_pass(t_scene *scene, t_ray *ray, int *pixel_color)
{
	if (ray->object_type == SEL_SPHERE)
		specular_sphere(scene, ray, pixel_color);
	else if (ray->object_type == SEL_PLANE)
		specular_plane(scene, ray, pixel_color);
	else if (ray->object_type == SEL_CYLINDER_CAP)
		specular_cyltop(scene, ray, pixel_color);
	else if (ray->object_type == SEL_CYLINDER_SIDE)
		specular_cylinder(scene, ray, pixel_color);
}
