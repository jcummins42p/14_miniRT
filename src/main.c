/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 14:50:05 by jcummins          #+#    #+#             */
/*   Updated: 2024/09/23 18:46:57 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	open_scenes(t_rt *rt, char **argv)
{
	int	i;

	i = -1;
	while (++i < rt->n_scenes)
	{
		rt->fd[i] = open(argv[i + 1], O_RDONLY);
		if (rt->fd[i] < 0)
			return (1);
	}
	return (0);
}

void	init_rt(t_rt *rt, int argc)
{
	rt->errcode = 0;
	rt->curr_scene = 0;
	rt->n_scenes = argc - 1;
	rt->fd = malloc(sizeof(int) * rt->n_scenes);
	rt->scenes = alloc_scenes(rt->n_scenes);
}

int	handle_destroy(t_mlx *mlx)
{
	k_press(0xff1b, mlx);
	return (0);
}

int	set_mlx(t_mlx *mlx, t_rt *rt)
{
	if (mlx == NULL || rt == NULL)
		return (1);
	mlx->mlx = mlx_init();
	if (mlx->mlx == NULL)
		return (2);
	mlx->win = mlx_new_window(mlx->mlx, RES_W, RES_H, "miniRT");
	if (mlx->win == NULL)
		return (3);
	mlx->rt = rt;
	mlx->aspect_ratio = RES_W / RES_H;
	mlx_hook(mlx->win, KeyPress, KeyPressMask, k_press, mlx);
	mlx_hook(mlx->win, KeyRelease, KeyReleaseMask, k_release, mlx);
	mlx_hook(mlx->win, ButtonPress, ButtonPressMask, b_press, mlx);
	mlx_hook(mlx->win, ButtonRelease, ButtonReleaseMask, b_release, mlx);
	mlx_hook(mlx->win, ON_DESTROY, ButtonPressMask, handle_destroy, mlx);
	return (0);
}

int	set_rt(int argc, char **argv, t_rt *rt)
{
	init_rt(rt, argc);
	init_scenes(rt, argv);
	if (!rt->scenes)
		return (1);
	if (open_scenes(rt, argv))
		return (1);
	preparse(rt);
	alloc_shapes(rt);
	open_scenes(rt, argv);
	parse(rt);
	return (0);
}

void	cleanup_mlx(t_mlx *mlx)
{
	if (!mlx)
		return ;
	free_rt(mlx->rt);
	mlx_destroy_window(mlx->mlx, mlx->win);
	mlx_destroy_display(mlx->mlx);
	if (mlx->mlx)
		free (mlx->mlx);
}

int	main(int argc, char **argv)
{
	t_mlx	mlx;
	t_rt	rt;

	if (argc < 2)
		exit_error(NULL, "Error: Wrong number of arguments\n", ERR_ARGC);
	if (set_mlx(&mlx, &rt))
		exit_error(&mlx, "Error: Failure to initialize mlx\n", ERR_ARGC);
	if (set_rt(argc, argv, &rt))
		exit_error(&mlx, "Error: Failure to parse input files\n", ERR_ARGC);
	print_scenes(&rt);
	mlx_loop(mlx.mlx);
	cleanup_mlx(&mlx);
	return (rt.errcode);
}
