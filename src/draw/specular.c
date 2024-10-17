/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specular.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 09:54:25 by jcummins          #+#    #+#             */
/*   Updated: 2024/10/17 13:46:43 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	specular_plane(t_scene *scene, t_ray *ray, int *pixel_color)
{
	t_plane		*plane;
	float		incidence;
	t_vec3		light;
	t_vec3		reflect;

	plane = (t_plane *)ray->object;
	vec3_a_to_b(light, scene->light.point, ray->bounce);
	vec3_normalize(light, light);
	if (dot_product(ray->udir, plane->norm) > 0)
		return ;
	vec3_surface_reflection(reflect, light, plane->norm);
	incidence = dot_product(ray->udir, reflect);
	if (incidence < 0)
		return ;
	incidence = (plane->shine / 100.0) * powf(incidence, plane->shine);
	*pixel_color = color_shift(*pixel_color, scene->light.hue, incidence);
}

void	specular_cyltop(t_scene *scene, t_ray *ray, int *pixel_color)
{
	t_cylinder	*cylinder;
	float		incidence;
	t_vec3		light;
	t_vec3		reflect;

	cylinder = (t_cylinder *)ray->object;
	vec3_a_to_b(light, scene->light.point, ray->bounce);
	vec3_normalize(light, light);
	vec3_surface_reflection(reflect, light, cylinder->axis);
	incidence = dot_product(ray->udir, reflect);
	if (incidence < 0)
		return ;
	incidence = (cylinder->shine / 100.0) * powf(incidence, cylinder->shine);
	*pixel_color = color_shift(*pixel_color, scene->light.hue, incidence);
}

void	specular_cylinder(t_scene *scene, t_ray *ray, int *pixel_color)
{
	t_cylinder	*cylinder;
	float		incidence;
	t_vec3		normal;
	t_vec3		light;
	t_vec3		reflect;

	cylinder = (t_cylinder *)ray->object;
	get_cylinder_normal(normal, cylinder, ray);
	vec3_a_to_b(light, scene->light.point, ray->bounce);
	vec3_normalize(light, light);
	vec3_surface_reflection(reflect, light, normal);
	incidence = dot_product(ray->udir, reflect);
	if (incidence < 0)
		return ;
	incidence = (cylinder->shine / 100.0) * powf(incidence, cylinder->shine);
	*pixel_color = color_shift(*pixel_color, scene->light.hue, incidence);
}

void	specular_sphere(t_scene *scene, t_ray *ray, int *pixel_color)
{
	t_sphere	*sphere;
	float		incidence;
	t_vec3		normal;
	t_vec3		light;
	t_vec3		reflect;

	sphere = (t_sphere *)ray->object;
	vec3_a_to_b(normal, sphere->center, ray->bounce);
	vec3_normalize(normal, normal);
	vec3_a_to_b(light, scene->light.point, ray->bounce);
	vec3_normalize(light, light);
	vec3_surface_reflection(reflect, light, normal);
	incidence = dot_product(ray->udir, reflect);
	if (incidence < 0)
		return ;
	incidence = (sphere->shine / 100.0) * powf(incidence, sphere->shine);
	*pixel_color = color_shift(*pixel_color, scene->light.hue, incidence);
}

void	specular_pass(t_scene *scene, t_ray *ray, int *pixel_color)
{
	if (ray->obj_type == SEL_SPHERE)
		specular_sphere(scene, ray, pixel_color);
	else if (ray->obj_type == SEL_PLANE)
		specular_plane(scene, ray, pixel_color);
	else if (ray->obj_type == SEL_CYLINDER_CAP)
		specular_cyltop(scene, ray, pixel_color);
	else if (ray->obj_type == SEL_CYLINDER_SIDE)
		specular_cylinder(scene, ray, pixel_color);
}
