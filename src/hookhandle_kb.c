/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hookhandle_kb.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:32:48 by jcummins          #+#    #+#             */
/*   Updated: 2024/09/23 13:41:18 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	k_no_event(void *vars)
{
	(void) vars;
	return (0);
}

int	k_release(int keysym, void *vars)
{
	ft_printf("Keyrelease: %d\n", keysym);
	(void) vars;
	return (0);
}

int	kp_scene_select(int keysym, t_mlx *mlx, int	newscene)
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
	print_scene(mlx->rt->scenes[newscene]);
	display_hud(mlx, mlx->rt->scenes[newscene]);
	return (newscene);
}

void	kp_scene_change(t_mlx *mlx, int newscene)
{
	if (mlx->rt->scenes[newscene]->valid)
		render_scene(mlx, mlx->rt->scenes[newscene]);
	else
		printf("Unable to render invalid scene\n");
}

int	k_select(int keysym, t_mlx *mlx)
{
	static int newscene;

	if (keysym == XK_KP_Add || keysym == XK_KP_Subtract)
		newscene = kp_scene_select(keysym, mlx, newscene);
	else if (keysym == XK_KP_Enter)
		kp_scene_change(mlx, newscene);
	else if (newscene >= 0 && newscene < mlx->rt->n_scenes)
	{
		printf("Acessing scene %d\n", newscene);
		mlx->rt->curr_scene = newscene;
		print_scene(mlx->rt->scenes[newscene]);
		render_scene(mlx, mlx->rt->scenes[newscene]);
		display_hud(mlx, mlx->rt->scenes[newscene]);
	}
	else
		printf("Invalid scene selected\n");
	return 0;
}

void	toggle_scan(t_mlx *mlx)
{
	int i;

	i = mlx->rt->curr_scene;
	if (mlx->rt->scenes[i]->rend.scan)
		mlx->rt->scenes[i]->rend.scan = false;
	else
		mlx->rt->scenes[i]->rend.scan = true;
}

int	k_press(int keysym, t_mlx *mlx)
{
	if (keysym == XK_Escape)
	{
		ft_printf("escape pressed\n");
		mlx_loop_end(mlx->mlx);
	}
	/*if (keysym == 115)*/
		/*toggle_scan(mlx);*/
	else
		k_select(keysym, mlx);
	ft_printf("Keypress: %d\n", keysym);
	return (0);
}
