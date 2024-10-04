/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_cam_ray.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 15:35:34 by jcummins          #+#    #+#             */
/*   Updated: 2024/10/04 13:54:09 by akretov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_color	cast_cam_ray(t_scene *scene, t_ray *ray)
{
	t_color	pixel_color;
	t_color	light_color;
	t_color	temp_color;
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
		pixel_color = shade_pixel_distance(pixel_color, closest_t);
	}
	else
		pixel_color = XCOL_BLK;
	return (pixel_color);
}

void	prep_cam_ray(t_mlx *mlx, t_scene *scene, int x, int y)
{
	t_color		pixel_color;
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
