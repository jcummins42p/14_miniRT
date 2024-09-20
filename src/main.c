/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 14:50:05 by jcummins          #+#    #+#             */
/*   Updated: 2024/09/20 19:38:44 by jcummins         ###   ########.fr       */
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
			return (i);
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

void	free_mlx(t_mlx *mlx)
{
	if (!mlx)
		return ;
	if (mlx->mlx)
		free (mlx->mlx);
	if (mlx->win)
		free (mlx->win);
}

int	handle_destroy(void *params)
{
	t_mlx	*mlx;

	mlx = params;
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
	mlx_hook(mlx->win, KeyPress, KeyPressMask, &k_press, mlx);
	mlx_hook(mlx->win, KeyRelease, KeyReleaseMask, &k_release, mlx);
	mlx_hook(mlx->win, ButtonPress, ButtonPressMask, &b_press, mlx);
	mlx_hook(mlx->win, ButtonRelease, ButtonReleaseMask, &b_release, mlx);
	mlx_hook(mlx->win, ON_DESTROY, ButtonPressMask, &handle_destroy, mlx);
	return (0);
}

void	cleanup_mlx(t_mlx *mlx)
{
	mlx_destroy_window(mlx->mlx, mlx->win);
	mlx_destroy_display(mlx->mlx);
	free(mlx->mlx);
}

int	main(int argc, char **argv)
{
	t_mlx	mlx;
	t_rt	rt;

	if (argc < 2)
		exit_error("Error: Wrong number of arguments", ERR_ARGC);
	if (set_mlx(&mlx, &rt))
	{
		free_mlx(&mlx);
		return (ERR_MLX);
	}
	init_rt(&rt, argc);
	init_scenes(&rt, argv);
	if (!rt.scenes)
		exit_error("Error: Failure to malloc scenes", ERR_MALLOC);
	if (open_scenes(&rt, argv))
		exit_error("Error: Failure to open files", ERR_ARGV);
	preparse(&rt);
	alloc_shapes(&rt);
	open_scenes(&rt, argv);
	parse(&rt);
	print_scenes(&rt);
	render_scene(&mlx, rt.scenes[0]);
	display_hud(&mlx);
	mlx_loop(mlx.mlx);
	cleanup_mlx(&mlx);
	free_scenes(&rt);
	free(rt.fd);
	return (0);
}
