/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_cam_ray.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 15:35:34 by jcummins          #+#    #+#             */
/*   Updated: 2024/10/18 14:13:14 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

float	find_closest_t(t_scene *scene, t_ray *ray, int *pixel_color)
{
	float	temp_t;

	temp_t = INFINITY;
	*pixel_color = -1;
	intersect_spheres(scene, ray, &temp_t, pixel_color);
	intersect_planes(scene, ray, &temp_t, pixel_color);
	intersect_cylinders(scene, ray, &temp_t, pixel_color);
	intersect_lights(scene, ray, &temp_t, pixel_color);
	return (temp_t);
}

int	cast_cam_ray(t_scene *scene, t_ray *ray)
{
	ray->obj_t = find_closest_t(scene, ray, &ray->obj_color);
	if (ray->obj_type == SEL_LIGHT)
		return (ray->light_color);
	if (ray->obj_color >= 0)
	{
		vec3_position(ray->bounce, *ray->origin, ray->udir, ray->obj_t);
		ray->light_color = prep_light_ray(scene, ray->bounce);
		ray->light_color = light_angle(scene, ray, ray->light_color);
		ray->comb_color = combine_lights(ray->light_color, scene->amb);
		ray->pixel_color = illuminate_pixel(ray->obj_color, ray->comb_color);
		if (ray->light_color >= 0 && scene->specular)
			specular_pass(scene, ray, &ray->pixel_color);
		ray->pixel_color = shade_pixel_distance(ray->pixel_color, ray->obj_t);
	}
	else
		ray->pixel_color = XCOL_BLK;
	return (ray->pixel_color);
}

void	init_cam_ray(t_scene *scene, t_ray *ray, int x, int y)
{
	ray->x = x;
	ray->y = y;
	ray->origin = &scene->cam.point;
	ray->obj_t = INFINITY;
	ray->obj_color = -1;
	ray->light_color = -1;
}

void	prep_cam_ray(t_mlx *mlx, t_scene *scene, int x, int y)
{
	int			pixel_color;
	t_ray		ray;
	t_vec2		ndc;
	t_vec2		viewport;

	scene->select_type[y][x] = SEL_NONE;
	scene->screen_object[y][x] = NULL;
	init_cam_ray(scene, &ray, x, y);
	norm_device_coords(ndc, x, y);
	project_viewport(viewport, ndc, scene->cam.fov, mlx->aspect_ratio);
	set_ray_direction(ray.dir, viewport, scene->cam);
	vec3_normalize(ray.udir, ray.dir);
	pixel_color = cast_cam_ray(scene, &ray);
	pixel_put_img(scene->img, x, y, pixel_color);
}
