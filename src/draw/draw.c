/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:02:30 by jcummins          #+#    #+#             */
/*   Updated: 2024/09/20 20:16:33 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	cast_ray(t_scene *scene, int x, int y)
{
	pixel_put(scene->img, x, y, scene->sky);
}

void	render_row(t_scene *scene, int y)
{
	int	x;

	x = 0;
	while (x < RES_W)
		cast_ray(scene, x++, y);
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
	if (img_init(mlx, scene->img))
		return ;
	while (y < RES_H)
		render_row(scene, y++);
	mlx_put_image_to_window(mlx->mlx, mlx->win, scene->img->img, 0, 0);
	mlx_destroy_image(mlx->mlx, scene->img->img);
}
