/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specular.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 09:54:25 by jcummins          #+#    #+#             */
/*   Updated: 2024/10/15 14:01:24 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

//	R = L - 2(L.N)N
//	results in a unit vector showing the reflection direction
void	vec3_surface_reflection(t_vec3 reflect, t_vec3 light, t_vec3 norm)
{
	t_vec3	light_u;
	float	dot_LN;

	vec3_normalize(light_u, light);
	dot_LN = dot_product(light, norm);
	vec3_scaleize(reflect, norm, 2 * dot_LN);
	vec3_a_to_b(reflect, light_u, reflect);
	vec3_normalize(reflect, reflect);
}

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
	if (coincidence < EPSILON)
		return ;
	coincidence = powf(coincidence, plane->shine);
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
	if (coincidence < EPSILON)
		return ;
	coincidence = powf(coincidence, sphere->shine);
	*pixel_color = color_shift(*pixel_color, scene->light.hue, coincidence);
}

void	specular_pass(t_scene *scene, t_ray *ray, int *pixel_color)
{
	if (ray->object_type == SEL_SPHERE)
		specular_sphere(scene, ray, pixel_color);
	else if (ray->object_type == SEL_PLANE)
		specular_plane(scene, ray, pixel_color);
}
