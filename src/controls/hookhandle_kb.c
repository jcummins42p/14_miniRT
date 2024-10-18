/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hookhandle_kb.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:32:48 by jcummins          #+#    #+#             */
/*   Updated: 2024/10/18 16:17:38 by akretov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	k_no_event(void *vars)
{
	(void) vars;
	return (0);
}

int	k_release(int ksym, void *vars)
{
	(void) vars;
	(void) ksym;
	return (0);
}

void	k_fov_controls(t_mlx *mlx, int ksym)
{
	int	*fov;

	fov = &mlx->rt->scenes[mlx->rt->curr_scene]->cam.fov;
	if (ksym == XK_Z)
		(*fov)++;
	else if (ksym == XK_X)
		(*fov)--;
	render_scene(mlx, mlx->rt->scenes[mlx->rt->curr_scene]);
}

int	check_key_object(int ksym, t_mlx *mlx)
{
	t_scene	*scene;

	scene = mlx->rt->scenes[mlx->rt->curr_scene];
	if ((ksym >= XK_KP_7 && ksym <= XK_KP_0)
		|| ksym == XK_KP_Q || ksym == XK_KP_W || ksym == XK_KP_E
		|| ksym == XK_KP_S || ksym == XK_KP_D
		|| ksym == XK_KP_R || ksym == XK_KP_T
		|| ksym == XK_KP_F || ksym == XK_KP_G
		|| (ksym == XK_KP_A && (scene->sel_type == SEL_CYLINDER_CAP
				|| scene->sel_type == SEL_CYLINDER_SIDE
				|| scene->sel_type == SEL_CAM)))
		return (1);
	return (0);
}

int	k_press(int ksym, t_mlx *mlx)
{
	if (ksym == XK_ESCAPE)
		mlx_loop_end(mlx->mlx);
	else if (check_key_object(ksym, mlx) == 1)
		k_directional_controls(ksym, mlx);
	else if (ksym == XK_KP_5)
		reset_cam_default(mlx, &mlx->rt->scenes[mlx->rt->curr_scene]->cam);
	else if (ksym == XK_KP_DELETE)
		k_deselect_object(mlx);
	else if (ksym == XK_KP_ADD || ksym == XK_KP_SUBTRACT
		|| ksym == XK_KP_ENTER)
		k_select_scene(ksym, mlx);
	else if (ksym == XK_M)
		toggle_bool(&mlx->multithread);
	else if (ksym == XK_A)
		k_select_ambient(mlx);
	else if (ksym == XK_P || ksym == XK_L)
		k_select_light(ksym, mlx);
	else if (ksym == XK_PERIOD || ksym == XK_COMMA || ksym == XK_BACKSLASH)
		k_adjust_shine(ksym, mlx);
	else if (ksym == XK_Z || ksym == XK_X)
		k_fov_controls(mlx, ksym);
	return (0);
}
