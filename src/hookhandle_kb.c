/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hookhandle_kb.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:32:48 by jcummins          #+#    #+#             */
/*   Updated: 2024/09/26 15:27:21 by jcummins         ###   ########.fr       */
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
	/*ft_printf("Keyrelease: %d\n", keysym);*/
	(void) vars;
	(void) keysym;
	return (0);
}

int	kp_scene_select(int keysym, t_mlx *mlx, int newscene)
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

void	kp_scene_change(t_mlx *mlx, int newscene)
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
		return (2);
	}
	else
		printf("Invalid scene selected\n");
	return (0);
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

int	k_cam_move(int keysym, t_mlx *mlx)
{
	if (keysym == 65362)
		mlx->rt->scenes[mlx->rt->curr_scene]->cam.point[_Y] += 1;
	else if (keysym == 65364)
		mlx->rt->scenes[mlx->rt->curr_scene]->cam.point[_Y] -= 1;
	else if (keysym == 65363)
		mlx->rt->scenes[mlx->rt->curr_scene]->cam.point[_X] += 1;
	else if (keysym == 65361)
		mlx->rt->scenes[mlx->rt->curr_scene]->cam.point[_X] -= 1;
	else
		return (0);
	return (1);
}

void	k_redraw(t_mlx *mlx, int redraw)
{
	if (redraw == 2)
		print_scene(mlx->rt->scenes[mlx->rt->curr_scene]);
	render_scene(mlx, mlx->rt->scenes[mlx->rt->curr_scene]);
	if (redraw == 2)
		display_hud(mlx, mlx->rt->scenes[mlx->rt->curr_scene]);
}

int	k_cam_pan(int keysym, t_mlx *mlx)
{
	if (keysym == 65431)
	{
		printf("Pointing camera forwards: ");
		printf("Old camera z: %f", mlx->rt->scenes[mlx->rt->curr_scene]->cam.dir[_Z]);
		mlx->rt->scenes[mlx->rt->curr_scene]->cam.dir[_Z] = 1.0;
		printf("New camera z: %f\n", mlx->rt->scenes[mlx->rt->curr_scene]->cam.dir[_Z]);
	}
	else if (keysym == 65433)
	{
		printf("Pointing camera backwards:");
		printf("Old camera z: %f", mlx->rt->scenes[mlx->rt->curr_scene]->cam.dir[_Z]);
		mlx->rt->scenes[mlx->rt->curr_scene]->cam.dir[_Z] = -1.0;
		printf("New camera z: %f\n", mlx->rt->scenes[mlx->rt->curr_scene]->cam.dir[_Z]);
	}
	else
		return (0);
	return (1);
}

int	k_press(int keysym, t_mlx *mlx)
{
	int	redraw;

	redraw = 0;
	printf("k_press %d\n", keysym);
	if (keysym == XK_Escape)
		mlx_loop_end(mlx->mlx);
	else if (keysym >= 65361 && keysym <= 65364)
		redraw = k_cam_move(keysym, mlx);
	else if (keysym >= 65429 && keysym <= 65436)
		redraw = k_cam_pan(keysym, mlx);
	else if (keysym == XK_KP_Add || keysym == XK_KP_Subtract || keysym == XK_KP_Enter)
		redraw = k_select(keysym, mlx);
	if (redraw)
		k_redraw(mlx, redraw);
	/*ft_printf("Keypress: %d\n", keysym);*/
	return (0);
}
