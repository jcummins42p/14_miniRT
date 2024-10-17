/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_scenes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 17:12:28 by jcummins          #+#    #+#             */
/*   Updated: 2024/10/17 17:15:20 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	kp_select_scene(int keysym, t_mlx *mlx, int newscene)
{
	t_rt	*rt;

	rt = mlx->rt;
	if (keysym == XK_KP_Add)
	{
		if (newscene < (rt->n_scenes - 1))
			newscene++;
	}
	else if (keysym == XK_KP_Subtract)
	{
		if (newscene > 0)
			newscene--;
	}
	display_hud(mlx, mlx->rt->scenes[newscene]);
	return (newscene);
}

void	kp_change_scene(t_mlx *mlx, int newscene)
{
	if (mlx->rt->scenes[newscene]->valid)
	{
		mlx->rt->curr_scene = newscene;
		render_scene(mlx, mlx->rt->scenes[newscene]);
		print_scene(mlx->rt->scenes[newscene]);
	}
	else
		printf("Unable to render invalid scene\n");
}

int	k_select_scene(int keysym, t_mlx *mlx)
{
	static int	newscene;

	if (keysym == XK_KP_Add || keysym == XK_KP_Subtract)
		newscene = kp_select_scene(keysym, mlx, newscene);
	else if (keysym == XK_KP_Enter)
		kp_change_scene(mlx, newscene);
	else if (newscene >= 0 && newscene < mlx->rt->n_scenes)
	{
		printf("Acessing scene %d\n", newscene);
		mlx->rt->curr_scene = newscene;
		return (2);
	}
	else
		printf("Invalid scene selected\n");
	return (0);
}
