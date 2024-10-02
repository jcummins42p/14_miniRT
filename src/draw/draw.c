/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:02:30 by jcummins          #+#    #+#             */
/*   Updated: 2024/10/02 16:10:00 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	pixel_put_img(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	safe_screenspace_radius(int x, int y, int radius)
{
	if (radius > x)
		radius = x;
	if ((x + radius) > RES_W)
		radius = RES_W - x;
	if (radius > y)
		radius = y;
	if ((y + radius) > RES_H)
		radius = RES_H - y;
	return (radius);
}

void	highlight_selected(t_scene *scene, int x, int y, int radius)
{
	if (!scene->selected || scene->screen_object[y][x] == scene->selected)
		return ;
	radius = safe_screenspace_radius(x, y, radius);
	if (scene->screen_object[y + radius][x + radius] == scene->selected
		|| scene->screen_object[y - radius][x + radius] == scene->selected
		|| scene->screen_object[y + radius][x - radius] == scene->selected
		|| scene->screen_object[y - radius][x - radius] == scene->selected)
	pixel_put_img(scene->img, x, y, XCOL_WHT);
}

/*void	add_light_bloom(t_scene *scene)*/
/*{*/
	/*char	*dst;*/

	/*dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));*/
	/**(unsigned int *)dst = color;*/
/*}*/

void	post_process(t_scene *scene, int x, int y)
{
	highlight_selected(scene, x, y, HIGHLIGHT_RAD);
	/*add_light_bloom(scene);*/
}

void	render_row(t_mlx *mlx, t_scene *scene, int y)
{
	int	x;

	x = 0;
	while (x < RES_W)
	{
		prep_cam_ray(mlx, scene, x, y);
		post_process(scene, x, y);
		x++;
	}
}

void	*render_row_mt(void *data)
{
	t_mlx	*mlx;
	t_scene	*scene;
	int		x;
	int		y;

	mlx = (t_mlx *)data;
	scene = mlx->rt->scenes[mlx->rt->curr_scene];
	pthread_mutex_lock(&mlx->mutex);
	y = mlx->y;
	pthread_mutex_unlock(&mlx->mutex);
	x = 0;
	if (y == 0)
	{
		while ( y < RES_H / 2)
		{
			x = 0;
			while (x < RES_W)
			{
				prep_cam_ray(mlx, scene, x, y);
				/*post_process(scene, x, y);*/
				x++;
			}
			y++;
		}
	}
	else if (y == 1)
	{
		y = RES_H / 2;
		while ( y < RES_H / 2)
		{
			x = 0;
			while (x < RES_W)
			{
				prep_cam_ray(mlx, scene, x, y);
				/*post_process(scene, x, y);*/
				x++;
			}
			y++;
		}
	}
	return (NULL);
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
	pthread_t	thread_id[RES_H];

	pthread_mutex_init(&mlx->mutex, NULL);
	pthread_mutex_unlock(&mlx->mutex);
	y = 0;
	mlx->y = 0;
	if (!scene->valid)
		return ;
	if (img_init(mlx, scene->img))
		return ;
	while (y < 2)
	{
		pthread_mutex_lock(&mlx->mutex);
		mlx->y = y;
		pthread_mutex_unlock(&mlx->mutex);
		pthread_create(&thread_id[y++], NULL, &render_row_mt, mlx);
		/*render_row(mlx, scene, y++);*/
	}
	printf("Finished render\n");
	while (y >= 0)
		pthread_join(thread_id[y--], NULL);
	if (!scene->rend.scan)
	{
		mlx_put_image_to_window(mlx->mlx, mlx->win, scene->img->img, 0, 0);
		mlx_destroy_image(mlx->mlx, scene->img->img);
	}
}
