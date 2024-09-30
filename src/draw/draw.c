/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:02:30 by jcummins          #+#    #+#             */
/*   Updated: 2024/09/30 18:40:42 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	pixel_put_img(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

//	sets a 2d normalized device vector for that co-ordinate's relative position
//	on the virtual screen between -1,-1 (top left) and 1,1 (bottom right) going
//	through 0,0 (center of screen)
void	norm_device_coords(t_vec2 ndc, int x, int y)
{
	ndc[_X] = ((2.0 * x) / RES_W) - 1.0;
	ndc[_Y] = 1.0 - ((2.0 * y) / RES_H);
}

//	uses the ndc vector to generate co-ordinate for that x,y on the virtual
//	screen. The relationship between fov (theta) and distance to image plane:
//	tan(theta/2) = ymax / d
//	where ymax it the distance from the middle of the screen to the top
void	project_viewport(t_vec2 project, t_vec2 ndc, int fov, float aspect)
{
	project[_X] = (ndc[_X] * aspect * fl_abs(tan(fov / 2.0)));
	project[_Y] = (ndc[_Y] * fl_abs(tan(fov / 2.0)));
}

void	set_ray_direction(t_vec3 dir, t_vec2 plane, t_camera cam)
{
	dir[_X] = cam.dir[_X] + cam.right[_X] * plane[_X] + cam.up[_X] * plane[_Y];
	dir[_Y] = cam.dir[_Y] + cam.right[_Y] * plane[_X] + cam.up[_Y] * plane[_Y];
	dir[_Z] = cam.dir[_Z] + cam.right[_Z] * plane[_X] + cam.up[_Z] * plane[_Y];
}

void	shade_pixel_distance(t_color *pixel_color, float distance)
{
	*pixel_color = color_shift(*pixel_color, 0x000000, distance);
}

//	first, shades pixel colour towards black inversely proprtional to luminence
//	then the colour is dim
void	shade_light_ambient(t_color *light_color, t_scene *scene)
{
	*light_color = color_shift(*light_color, 0x000000, 1 - scene->amb.lum);
	/**pixel_color = color_subtract(*pixel_color, color_invert(scene->amb.hue), scene->amb.lum);*/
}

t_color	combine_lights(t_color light_color, t_ambient amb)
{
	t_color	amb_color;

	amb_color = color_shift(amb.hue, 0x000000, 1 - amb.lum);
	return (color_addition(light_color, amb_color));
}

void	shade_pixel_dirlight(t_scene *scene, t_color *pixel_color, t_color light_color)
{
	/*float	ratio;*/

	(void)scene;
	/*ratio = 1;*/
	/*(void)distance;*/
	/**pixel_color = color_illuminate(*pixel_color, light_color, ratio);*/
	/**pixel_color = color_shift(*pixel_color, light_color, (distance / 100));*/
	*pixel_color = color_subtract(*pixel_color, color_invert(light_color), 1);
}

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
		shade_pixel_distance(&light_color, (DARK * log(light_t / (BRIGHT))));
	return (light_color);
}

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
	temp_color = intersect_lights(scene, ray, &temp_t);
	if (temp_t < closest_t)
	{
		closest_t = 0;	//	setting closest distance to 0 for lights keeps brightness max
		pixel_color = temp_color;
	}
	if (pixel_color >= 0)
	{
		vec3_position(ray->bounce, *ray->origin, ray->udir, closest_t);
		light_color = prep_light_ray(scene, ray->bounce);
		light_color = combine_lights(light_color, scene->amb);
		shade_pixel_dirlight(scene, &pixel_color, light_color);
		pixel_color = color_shift(pixel_color, 0x000000, (closest_t / 100));
	}
	else
		pixel_color = 0x000000;
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

void	render_row(t_mlx *mlx, t_scene *scene, int y)
{
	int	x;

	x = 0;
	while (x < RES_W)
		prep_cam_ray(mlx, scene, x++, y);
}

int	img_init(t_mlx *mlx, t_img *img)
{
	img->img = mlx_new_image(mlx->mlx, RES_W, RES_H);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, \
				&img->line_length, &img->endian);
	if (!img->img || !img->addr)
	{
		printf("Failed to create img\n");
		return (1);
	}
	return (0);
}

void	render_scene(t_mlx *mlx, t_scene *scene)
{
	int			y;

	y = 0;
	if (!scene->valid)
		return ;
	if (img_init(mlx, scene->img))
		return ;
	while (y < RES_H)
		render_row(mlx, scene, y++);
	if (!scene->rend.scan)
	{
		mlx_put_image_to_window(mlx->mlx, mlx->win, scene->img->img, 0, 0);
		mlx_destroy_image(mlx->mlx, scene->img->img);
	}
}
