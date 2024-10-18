/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene_mt.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:01:55 by jcummins          #+#    #+#             */
/*   Updated: 2024/10/18 16:41:16 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	*render_row_mt(void *data)
{
	t_render	*render;
	t_mlx		*mlx;
	t_scene		*scene;
	int			coords[2];

	render = (t_render *)data;
	mlx = render->mlx;
	coords[_Y] = render->y;
	scene = mlx->rt->scenes[mlx->rt->curr_scene];
	coords[_X] = -1;
	while (++coords[_X] < RES_W)
		prep_cam_ray(mlx, scene, coords[_X], coords[_Y]);
	return (NULL);
}

static int	init_rqueue(t_mlx *mlx, t_render **renders)
{
	int	y;

	y = -1;
	*renders = malloc(sizeof(t_render) * RES_H + 1);
	if (!(*renders))
	{
		mlx->rt->errcode = ERR_MALLOC;
		return (1);
	}
	while (++y < RES_H)
	{
		(*renders)[y].thread_id = 0;
		(*renders)[y].mlx = mlx;
		(*renders)[y].y = y;
	}
	return (0);
}

static int	create_threads(t_render *renders, int n_threads)
{
	int	done_threads;
	int	y;

	y = -1;
	done_threads = 0;
	while (y < RES_H)
	{
		while (++y < n_threads + done_threads && y < RES_H)
		{
			if (pthread_create(&renders[y].thread_id,
					NULL, &render_row_mt, &renders[y]))
				return (1);
		}
		while (--y >= done_threads)
		{
			if (pthread_join(renders[y].thread_id, NULL))
				return (1);
		}
		done_threads += n_threads;
		y += n_threads;
	}
	return (0);
}

int	render_scene_mt(t_mlx *mlx, t_scene *scene)
{
	t_render	*renders;
	int			n_threads;

	n_threads = sysconf(_SC_NPROCESSORS_CONF);
	renders = NULL;
	if (!scene->valid
		|| img_init(mlx, scene->img)
		|| init_rqueue(mlx, &renders))
		return (1);
	if (create_threads(renders, n_threads))
		return (1);
	free(renders);
	return (0);
}
