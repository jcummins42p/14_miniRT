/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:41:50 by jcummins          #+#    #+#             */
/*   Updated: 2024/09/23 13:33:18 by jcummins         ###   ########.fr       */
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

void	display_hud(t_mlx *mlx, t_scene *scene)
{
	int		yi;
	int		y[20] = {60, 80, 100, 120, 140, 160, 180, 200, 220, 240, 260};
	int		x = 50;
	char	*id;

	yi = 0;
	id = ft_itoa(scene->id);
	display_hud_background(mlx);
	mlx_string_put(mlx->mlx, mlx->win, x, y[yi], 0xFFFFFF, "Scene #");
	mlx_string_put(mlx->mlx, mlx->win, x + 45, y[yi++], 0xFFFFFF, id);
	mlx_string_put(mlx->mlx, mlx->win, x, y[yi++], 0xFFFFFF, scene->fname);
	if (!scene->valid)
		mlx_string_put(mlx->mlx, mlx->win, x, y[yi++], 0xFF1111, \
				"*** INPUT SCENE INVALID: CANNOT RENDER***");
	free(id);
}
