/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:02:30 by jcummins          #+#    #+#             */
/*   Updated: 2024/10/02 12:14:15 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	pixel_put_img(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	render_row(t_mlx *mlx, t_scene *scene, int y)
{
	int	x;

	x = 0;
	while (x < RES_W)
	{
		prep_cam_ray(mlx, scene, x, y);
		if (scene->selected && (scene->screen_object[y][x] != scene->selected) &&
			(scene->screen_object[y + 2][x + 2] == scene->selected
			|| scene->screen_object[y - 2][x - 2] == scene->selected
			|| scene->screen_object[y + 2][x - 2] == scene->selected
			|| scene->screen_object[y - 2][x + 2] == scene->selected))
		{
			pixel_put_img(scene->img, x, y, XCOL_WHT);
		}
		x++;
	}
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
