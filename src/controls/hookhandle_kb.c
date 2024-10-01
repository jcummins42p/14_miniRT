/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hookhandle_kb.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:32:48 by jcummins          #+#    #+#             */
/*   Updated: 2024/10/01 19:41:55 by jcummins         ###   ########.fr       */
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

int	k_scene_select(int keysym, t_mlx *mlx)
{
	static int	newscene;

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
	int	i;

	i = mlx->rt->curr_scene;
	if (mlx->rt->scenes[i]->rend.scan)
		mlx->rt->scenes[i]->rend.scan = false;
	else
		mlx->rt->scenes[i]->rend.scan = true;
}

void	k_redraw(t_mlx *mlx, int redraw)
{
	if (redraw == 2)
		print_scene(mlx->rt->scenes[mlx->rt->curr_scene]);
	render_scene(mlx, mlx->rt->scenes[mlx->rt->curr_scene]);
	if (redraw == 2)
		display_hud(mlx, mlx->rt->scenes[mlx->rt->curr_scene]);
}

void	k_cam_pan(int keysym, t_camera *cam)
{
	char		*angles[4];
	static int	curr;

	angles[0] = "0,0,1";
	angles[1] = "-1,0,0";
	angles[2] = "0,0,-1";
	angles[3] = "1,0,0";
	if (keysym == XK_KP_7)
		curr++;
	else if (keysym == XK_KP_9)
		curr--;
	if (curr < 0)
		curr = 3;
	else if (curr > 3)
		curr = 0;
	set_vec3(cam->dir, angles[curr]);
	orient_camera(cam);
}

void	reset_cam_default(t_mlx *mlx, t_camera *cam)
{
	vec3_set_a(cam->point, cam->point_def);
	vec3_set_a(cam->dir, cam->dir_def);
	orient_camera(cam);
	render_scene(mlx, mlx->rt->scenes[mlx->rt->curr_scene]);
}

void	k_object_deselect(t_mlx *mlx)
{
	mlx->rt->scenes[mlx->rt->curr_scene]->selected = NULL;
	mlx->rt->scenes[mlx->rt->curr_scene]->sel_type = SEL_CAM;
	render_scene(mlx, mlx->rt->scenes[mlx->rt->curr_scene]);
}

int	k_press(int keysym, t_mlx *mlx)
{
	printf("k_press %d\n", keysym);
	if (keysym == XK_Escape)
		mlx_loop_end(mlx->mlx);
	else if (keysym == XK_KP_5)
		reset_cam_default(mlx, &mlx->rt->scenes[mlx->rt->curr_scene]->cam);
	else if (keysym >= XK_KP_7 && keysym <= XK_KP_0)
		k_directional_controls(keysym, mlx);
	else if (keysym == XK_KP_Delete)
		k_object_deselect(mlx);
	else if (keysym == XK_KP_Add || keysym == XK_KP_Subtract
		|| keysym == XK_KP_Enter)
		k_scene_select(keysym, mlx);
	return (0);
}
