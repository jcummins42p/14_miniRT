/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_cam_ray.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 15:35:34 by jcummins          #+#    #+#             */
/*   Updated: 2024/10/14 20:29:39 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	specular_plane(t_scene *scene, t_ray *ray, int *pixel_color)
{
	t_plane		*plane;
	float		angle_cam;
	float		angle_light;
	float		coincidence;
	t_vec3		light;

	plane = (t_plane *)ray->object;
	vec3_a_to_b(light, scene->light.point, ray->bounce);
	vec3_normalize(light, light);
	angle_light = dot_product(light, plane->norm);
	angle_cam = dot_product(ray->udir, plane->norm);
	coincidence = fl_abs(angle_light - angle_cam);
	if (coincidence > 0.999999)
		return ;
	*pixel_color = color_shift(*pixel_color, scene->light.hue, coincidence);
}

void	specular_sphere(t_scene *scene, t_ray *ray, int *pixel_color)
{
	t_sphere	*sphere;
	float		angle_cam;
	float		angle_light;
	float		coincidence;
	t_vec3		normal;
	t_vec3		light;

	sphere = (t_sphere *)ray->object;
	vec3_a_to_b(normal, sphere->center, ray->bounce);
	vec3_a_to_b(light, scene->light.point, ray->bounce);
	vec3_normalize(light, light);
	vec3_normalize(normal, normal);
	angle_light = dot_product(light, normal);
	angle_cam = dot_product(ray->udir, normal);
	coincidence = fl_abs(angle_light - angle_cam);
	if (coincidence > 0.999999)
		return ;
	*pixel_color = color_shift(*pixel_color, scene->light.hue, coincidence);
}

void	specular_pass(t_scene *scene, t_ray *ray, int *pixel_color)
{
	if (ray->object_type == SEL_SPHERE)
		specular_sphere(scene, ray, pixel_color);
	else if (ray->object_type == SEL_PLANE)
		specular_plane(scene, ray, pixel_color);
}

int	cast_cam_ray(t_scene *scene, t_ray *ray)
{
	int		pixel_color;
	int		light_color;
	int		temp_color;
	float	closest_t;
	float	temp_t;

	closest_t = INFINITY;
	temp_t = INFINITY;
	pixel_color = -1;
	scene->select_type[ray->y][ray->x] = SEL_NONE;
	scene->screen_object[ray->y][ray->x] = NULL;
	temp_color = intersect_spheres(scene, ray, &temp_t);
	if (temp_t < closest_t)
	{
		closest_t = temp_t;
		pixel_color = temp_color;
	}
	temp_color = intersect_planes(scene, ray, &temp_t);
	if (temp_t < closest_t)
	{
		closest_t = temp_t;
		pixel_color = temp_color;
	}
	temp_color = intersect_cylinders(scene, ray, &temp_t);
	if (temp_t < closest_t)
	{
		closest_t = temp_t;
		pixel_color = temp_color;
	}
	temp_color = intersect_lights(scene, ray, &temp_t);
	if (temp_t < closest_t)
		return (scene->light.hue);
	if (pixel_color >= 0)
	{
		vec3_position(ray->bounce, *ray->origin, ray->udir, closest_t);
		light_color = prep_light_ray(scene, ray->bounce);

		light_color = light_angle(scene, ray, light_color);
		// modulate light based on angle of normal to light source

		light_color = combine_lights(light_color, scene->amb);
		pixel_color = illuminate_pixel(pixel_color, light_color);
		specular_pass(scene, ray, &pixel_color);
		pixel_color = shade_pixel_distance(pixel_color, closest_t);
	}
	else
		pixel_color = XCOL_BLK;
	return (pixel_color);
}

void	prep_cam_ray(t_mlx *mlx, t_scene *scene, int x, int y)
{
	int		pixel_color;
	t_ray		ray;
	t_vec2		ndc;
	t_vec2		viewport;

	ray.x = x;
	ray.y = y;
	ray.origin = &scene->cam.point;
	norm_device_coords(ndc, x, y);
	project_viewport(viewport, ndc, scene->cam.fov, mlx->aspect_ratio);
	set_ray_direction(ray.dir, viewport, scene->cam);
	vec3_normalize(ray.udir, ray.dir);
	pixel_color = cast_cam_ray(scene, &ray);
	pixel_put_img(scene->img, x, y, pixel_color);
}
