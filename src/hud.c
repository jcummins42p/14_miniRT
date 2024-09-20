/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:41:50 by jcummins          #+#    #+#             */
/*   Updated: 2024/09/20 18:58:25 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	display_hud(t_mlx *mlx)
{
	int		curr;
	int		xi;
	int		yi;
	int		x[20] = {50, 70, 90, 110, 130, 150, 170, 190, 210, 230, 250};
	int		y = 50;
	t_scene	*scene;
	char	*id;

	xi = 0;
	yi = 0;
	curr = mlx->rt->curr_scene;
	scene = mlx->rt->scenes[curr];
	id = ft_itoa(scene->id);
	mlx_string_put(mlx->mlx, mlx->win, y, x[xi], 0x777777, "Scene #");
	mlx_string_put(mlx->mlx, mlx->win, y + 45, x[xi], 0x777777, id);
	mlx_string_put(mlx->mlx, mlx->win, y + 55, x[xi++], 0x777777, scene->fname);
	mlx_string_put(mlx->mlx, mlx->win, y, x[xi], 0x777777, "Scene #");
	mlx_string_put(mlx->mlx, mlx->win, y + 45, x[xi], 0x777777, id);
	mlx_string_put(mlx->mlx, mlx->win, y + 55, x[xi++], 0x777777, scene->fname);
	mlx_string_put(mlx->mlx, mlx->win, y, x[xi], 0x777777, "Scene #");
	mlx_string_put(mlx->mlx, mlx->win, y + 45, x[xi], 0x777777, id);
	mlx_string_put(mlx->mlx, mlx->win, y + 55, x[xi++], 0x777777, scene->fname);
	free(id);
}
