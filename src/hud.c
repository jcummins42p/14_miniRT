/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:41:50 by jcummins          #+#    #+#             */
/*   Updated: 2024/10/17 17:41:11 by akretov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	display_hud_background(t_mlx *mlx)
{
	int	x;
	int	y;

	x = 25;
	y = 25;
	while (y++ < 120)
	{
		x = 25;
		while (x < 340)
			mlx_pixel_put(mlx->mlx, mlx->win, x++, y, 0x000000);
	}
}

void	fill_array(int *y)
{
	int	i;

	i = -1;
	while (++i < 20)
		y[i] = 40 + 10 * i;
}

void	display_hud(t_mlx *mlx, t_scene *scene)
{
	int		yi;
	int		y[20];
	int		x;
	char	*id;

	yi = 0;
	x = 50;
	id = ft_itoa(scene->id);
	fill_array(y);
	display_hud_background(mlx);
	mlx_string_put(mlx->mlx, mlx->win, x, y[yi], 0xFFFFFF, "Scene #");
	mlx_string_put(mlx->mlx, mlx->win, x + 45, y[yi++], 0xFFFFFF, id);
	mlx_string_put(mlx->mlx, mlx->win, x, y[yi++], 0xFFFFFF, scene->fname);
	if (!scene->valid)
		mlx_string_put(mlx->mlx, mlx->win, x, y[yi++], 0xFF1111, \
				"*** INPUT SCENE INVALID: CANNOT RENDER***");
	free(id);
}
