/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_move.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 12:18:20 by jcummins          #+#    #+#             */
/*   Updated: 2024/10/03 19:05:17 by akretov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	k_move_light(int keysym, t_scene *scene)
{
	float		z_dir;
	t_light		*light;

	light = scene->selected;
	z_dir = scene->cam.dir[_Z];
	if (keysym == XK_KP_3)
		light->point[_Y] += 1;
	else if (keysym == XK_KP_1)
		light->point[_Y] -= 1;
	else if (keysym == XK_KP_6)
		light->point[_X] += 1 * z_dir;
	else if (keysym == XK_KP_4)
		light->point[_X] -= 1 * z_dir;
	else if (keysym == XK_KP_8)
		light->point[_Z] += 1 * z_dir;
	else if (keysym == XK_KP_2)
		light->point[_Z] -= 1 * z_dir;
	else if (keysym == XK_KP_9)
		light->lum += 0.05;
	else if (keysym == XK_KP_7)
		light->lum -= 0.05;
	if (light->lum > 1)
		light->lum = 1;
	if (light->lum < 0)
		light->lum = 0;
}

void	k_move_plane(int keysym, t_scene *scene)
{
	float	z_dir;
	t_plane	*plane;

	plane = scene->selected;
	z_dir = scene->cam.dir[_Z];
	if (keysym == XK_KP_3)
		plane->anch[_Y] += 1;
	else if (keysym == XK_KP_1)
		plane->anch[_Y] -= 1;
	else if (keysym == XK_KP_6)
		plane->anch[_X] += 1 * z_dir;
	else if (keysym == XK_KP_4)
		plane->anch[_X] -= 1 * z_dir;
	else if (keysym == XK_KP_8)
		plane->anch[_Z] += 1 * z_dir;
	else if (keysym == XK_KP_2)
		plane->anch[_Z] -= 1 * z_dir;
}

void	k_move_sphere(int keysym, t_scene *scene)
{
	float		z_dir;
	t_sphere	*sphere;

	sphere = scene->selected;
	z_dir = scene->cam.dir[_Z];
	if (keysym == XK_KP_3)
		sphere->center[_Y] += 1;
	else if (keysym == XK_KP_1)
		sphere->center[_Y] -= 1;
	else if (keysym == XK_KP_6)
		sphere->center[_X] += 1 * z_dir;
	else if (keysym == XK_KP_4)
		sphere->center[_X] -= 1 * z_dir;
	else if (keysym == XK_KP_8)
		sphere->center[_Z] += 1 * z_dir;
	else if (keysym == XK_KP_2)
		sphere->center[_Z] -= 1 * z_dir;
	else if (keysym == XK_KP_9)
		sphere->radius += 0.05;
	else if (keysym == XK_KP_7)
		sphere->radius -= 0.05;
}

void	k_move_camera(int keysym, t_scene *scene)
{
	float		z_dir;

	z_dir = scene->cam.dir[_Z];
	if (keysym == XK_KP_3)
		scene->cam.point[_Y] += 1;
	else if (keysym == XK_KP_1)
		scene->cam.point[_Y] -= 1;
	else if (keysym == XK_KP_6)
		scene->cam.point[_X] += 1 * z_dir;
	else if (keysym == XK_KP_4)
		scene->cam.point[_X] -= 1 * z_dir;
	else if (keysym == XK_KP_8)
		scene->cam.point[_Z] += 1 * z_dir;
	else if (keysym == XK_KP_2)
		scene->cam.point[_Z] -= 1 * z_dir;
	else if (keysym == XK_KP_7 || keysym == XK_KP_9)
		k_cam_pan(keysym, &scene->cam);
}

void	k_directional_controls(int keysym, t_mlx *mlx)
{
	printf("in directional controls\n");
	if (mlx->rt->scenes[mlx->rt->curr_scene]->sel_type == SEL_SPHERE)
		k_move_sphere(keysym, mlx->rt->scenes[mlx->rt->curr_scene]);
	else if (mlx->rt->scenes[mlx->rt->curr_scene]->sel_type == SEL_LIGHT)
		k_move_light(keysym, mlx->rt->scenes[mlx->rt->curr_scene]);
	else if (mlx->rt->scenes[mlx->rt->curr_scene]->sel_type == SEL_PLANE)
		k_move_plane(keysym, mlx->rt->scenes[mlx->rt->curr_scene]);
	else if (mlx->rt->scenes[mlx->rt->curr_scene]->sel_type == SEL_CAM)
		k_move_camera(keysym, mlx->rt->scenes[mlx->rt->curr_scene]);
	render_scene(mlx, mlx->rt->scenes[mlx->rt->curr_scene]);
}
