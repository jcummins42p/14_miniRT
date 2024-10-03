/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 11:48:29 by jcummins          #+#    #+#             */
/*   Updated: 2024/10/03 14:08:27 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	handle_destroy(t_mlx *mlx)
{
	k_press(0xff1b, mlx);
	return (0);
}

void	cleanup_mlx(t_mlx *mlx)
{
	if (!mlx)
		return ;
	cleanup_rt(mlx->rt);
	mlx_destroy_window(mlx->mlx, mlx->win);
	mlx_destroy_display(mlx->mlx);
	if (mlx->mlx)
		free (mlx->mlx);
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
	if (MULTITHREAD)
		mlx->multithread = true;
	else
		mlx->multithread = false;
	mlx_hook(mlx->win, KeyPress, KeyPressMask, k_press, mlx);
	mlx_hook(mlx->win, KeyRelease, KeyReleaseMask, k_release, mlx);
	mlx_hook(mlx->win, ButtonPress, ButtonPressMask, b_press, mlx);
	mlx_hook(mlx->win, ButtonRelease, ButtonReleaseMask, b_release, mlx);
	mlx_hook(mlx->win, ON_DESTROY, ButtonPressMask, handle_destroy, mlx);
	return (0);
}

