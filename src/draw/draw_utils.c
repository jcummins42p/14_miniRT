/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 15:39:25 by jcummins          #+#    #+#             */
/*   Updated: 2024/10/18 12:30:37 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	img_init(t_mlx *mlx, t_img *img)
{
	int	y;
	int	x;

	x = -1;
	y = -1;
	img->img = mlx_new_image(mlx->mlx, RES_W, RES_H);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, \
				&img->line_length, &img->endian);
	if (!img->img || !img->addr)
	{
		printf("Failed to create img\n");
		return (1);
	}
	while (++y < RES_H)
	{
		while (++x < RES_W)
			pixel_put_img(img, x, y, XCOL_WHT);
	}
	return (0);
}

void	pixel_put_img(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	color_int_to_vector(t_rgb rgb, int color)
{
	rgb[_R] = (color >> 16) & 0xFF;
	rgb[_G] = (color >> 8) & 0xFF;
	rgb[_B] = (color) & 0xFF;
}

int	color_vector_to_int(t_rgb rgb)
{
	int		color;

	color = 0;
	color += rgb[_R] << 16;
	color += rgb[_G] << 8;
	color += rgb[_B];
	return (color);
}
