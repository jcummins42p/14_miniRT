/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene_st.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:02:30 by jcummins          #+#    #+#             */
/*   Updated: 2024/10/18 16:00:46 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	render_row(t_mlx *mlx, t_scene *scene, int y)
{
	int	x;

	x = 0;
	while (x < RES_W)
	{
		scene->select_type[y][x] = SEL_NONE;
		scene->screen_object[y][x] = NULL;
		prep_cam_ray(mlx, scene, x, y);
		x++;
	}
}

static int	render_scene_st(t_mlx *mlx, t_scene *scene)
{
	int				y;

	y = 0;
	if (!scene->valid)
		return (1);
	if (img_init(mlx, scene->img))
		return (1);
	y = -1;
	while (++y < RES_H)
		render_row(mlx, scene, y);
	return (0);
}

int	render_scene(t_mlx *mlx, t_scene *scene)
{
	if (mlx->multithread)
	{
		if (render_scene_mt(mlx, scene))
			return (1);
	}
	else
	{
		if (render_scene_st(mlx, scene))
			return (1);
	}
	post_process(scene);
	mlx_put_image_to_window(mlx->mlx, mlx->win, scene->img->img, 0, 0);
	mlx_destroy_image(mlx->mlx, scene->img->img);
	return (0);
}
