/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:02:30 by jcummins          #+#    #+#             */
/*   Updated: 2024/10/17 15:58:39 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	render_row(t_mlx *mlx, t_scene *scene, int y)
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

void	*render_row_mt(void *data)
{
	t_render_queue	*render;
	t_mlx			*mlx;
	t_scene			*scene;
	int				coords[2];

	render = (t_render_queue *)data;
	mlx = render->mlx;
	coords[_Y] = render->y;
	scene = mlx->rt->scenes[mlx->rt->curr_scene];
	coords[_X] = 0;
	while (coords[_X] < RES_W)
	{
		prep_cam_ray(mlx, scene, coords[_X], coords[_Y]);
		coords[_X]++;
	}
	return (NULL);
}

int	render_scene_st(t_mlx *mlx, t_scene *scene)
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

int	init_rqueue(t_mlx *mlx, t_render_queue **renders)
{
	int	y;

	y = -1;
	*renders = malloc(sizeof(t_render_queue) * RES_H + 1);
	if (!(*renders))
	{
		mlx->rt->errcode = ERR_MALLOC;
		return (1);
	}
	while (++y < RES_H)
	{
		(*renders)[y].mlx = mlx;
		(*renders)[y].y = y;
	}
	return (0);
}

int	render_scene_mt(t_mlx *mlx, t_scene *scene)
{
	t_render_queue	*renders;
	int				y;
	pthread_t		thread_id[RES_H];

	renders = NULL;
	if (!scene->valid
			|| img_init(mlx, scene->img)
			|| init_rqueue(mlx, &renders))
		return (1);
	y = -1;
	while (++y < RES_H)
		thread_id[y] = 0;
	y = -1;
	while (++y < RES_H)
		pthread_create(&thread_id[y], NULL, &render_row_mt, &renders[y]);
	while (--y >= 0)
		pthread_join(thread_id[y], NULL);
	free(renders);
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
