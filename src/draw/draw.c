/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:02:30 by jcummins          #+#    #+#             */
/*   Updated: 2024/09/24 21:17:38 by jcummins         ###   ########.fr       */
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
	ndc[_X] = (2.0 * x) / RES_W - 1.0;
	ndc[_Y] = 1.0 - (2.0 * y) / RES_H;
}

//	uses the ndc vector to generate co-ordinate for that x,y on the virtual
//	screen.
void	project_viewport(t_vec2 project, t_vec2 ndc, int fov, float aspect)
{
	project[_X] = ndc[_X] * aspect * tan(fov / 2.0);
	project[_Y] = ndc[_Y] * tan(fov / 2.0);
}

void	set_ray_direction(t_vec3 dir, t_vec2 plane, t_camera cam)
{
	dir[_X] = cam.dir[_X] + cam.right[_X] * plane[_X] + cam.up[_X] * plane[_Y];
	dir[_Y] = cam.dir[_Y] + cam.right[_Y] * plane[_X] + cam.up[_Y] * plane[_Y];
	dir[_Z] = cam.dir[_Z] + cam.right[_Z] * plane[_X] + cam.up[_Z] * plane[_Y];
}

void	shade_pixel(t_color *pixel_color, float distance)
{
	*pixel_color = color_gradient(*pixel_color, 0x000000, distance);
}

t_color	cast_ray(t_scene *scene, t_ray *ray)
{
	t_color	pixel_color;
	t_color	temp_color;
	float	closest_t;
	float	temp_t;

	closest_t = INFINITY;
	temp_t = INFINITY;
	/*pixel_color = scene->sky;*/
	pixel_color = 0x000000;
	temp_color = intersect_planes(scene, ray, &temp_t);
	if (temp_t < closest_t)
	{
		closest_t = temp_t;
		printf("%.3f ", closest_t);
		pixel_color = temp_color;
		shade_pixel(&pixel_color, closest_t / 100);
	}
	return (pixel_color);
}

void	prep_ray(t_mlx *mlx, t_scene *scene, int x, int y)
{
	t_color		pixel_color;
	t_ray		ray;
	t_vec2		ndc;
	t_vec2		viewport;

	ray.origin = &scene->cam.point;
	norm_device_coords(ndc, x, y);
	project_viewport(viewport, ndc, scene->cam.fov, mlx->aspect_ratio);
	set_ray_direction(ray.dir, viewport, scene->cam);
	vector_normalize(ray.dir, ray.dir);

	pixel_color = cast_ray(scene, &ray);
	pixel_put_img(scene->img, x, y, pixel_color);
}

void	render_row(t_mlx *mlx, t_scene *scene, int y)
{
	int	x;

	x = 0;
	while (x < RES_W)
		prep_ray(mlx, scene, x++, y);
	printf("\n");
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
	int	y;

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
