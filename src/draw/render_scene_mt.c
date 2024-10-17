/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene_mt.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:01:55 by jcummins          #+#    #+#             */
/*   Updated: 2024/10/17 16:36:49 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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
	coords[_X] = -1;
	while (++coords[_X] < RES_W)
		prep_cam_ray(mlx, scene, coords[_X], coords[_Y]);
	return (NULL);
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
