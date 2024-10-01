/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_move.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 12:18:20 by jcummins          #+#    #+#             */
/*   Updated: 2024/10/01 16:33:32 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	k_move_light(int keysym, t_scene *scene)
{
	float		z_dir;
	t_light		*light;

	light = scene->selected;
	z_dir = scene->cam.dir[_Z];
	if (keysym == 65362)
		light->point[_Y] += 1;
	else if (keysym == 65364)
		light->point[_Y] -= 1;
	else if (keysym == 65432)
		light->point[_X] += 1 * z_dir;
	else if (keysym == 65430)
		light->point[_X] -= 1 * z_dir;
	else if (keysym == 65431)
		light->point[_Z] += 1 * z_dir;
	else if (keysym == 65433)
		light->point[_Z] -= 1 * z_dir;
}

void	k_move_plane(int keysym, t_scene *scene)
{
	float	z_dir;
	t_plane	*plane;

	plane = scene->selected;
	z_dir = scene->cam.dir[_Z];
	if (keysym == 65362)
		plane->anch[_Y] += 1;
	else if (keysym == 65364)
		plane->anch[_Y] -= 1;
	else if (keysym == 65432)
		plane->anch[_X] += 1 * z_dir;
	else if (keysym == 65430)
		plane->anch[_X] -= 1 * z_dir;
	else if (keysym == 65431)
		plane->anch[_Z] += 1 * z_dir;
	else if (keysym == 65433)
		plane->anch[_Z] -= 1 * z_dir;
}

void	k_move_sphere(int keysym, t_scene *scene)
{
	float		z_dir;
	t_sphere	*sphere;

	sphere = scene->selected;
	z_dir = scene->cam.dir[_Z];
	if (keysym == 65362)
		sphere->center[_Y] += 1;
	else if (keysym == 65364)
		sphere->center[_Y] -= 1;
	else if (keysym == 65432)
		sphere->center[_X] += 1 * z_dir;
	else if (keysym == 65430)
		sphere->center[_X] -= 1 * z_dir;
	else if (keysym == 65431)
		sphere->center[_Z] += 1 * z_dir;
	else if (keysym == 65433)
		sphere->center[_Z] -= 1 * z_dir;
}

void	k_move_camera(int keysym, t_scene *scene)
{
	float		z_dir;

	z_dir = scene->cam.dir[_Z];
	if (keysym == 65362)
		scene->cam.point[_Y] += 1;
	else if (keysym == 65364)
		scene->cam.point[_Y] -= 1;
	else if (keysym == 65432)
		scene->cam.point[_X] += 1 * z_dir;
	else if (keysym == 65430)
		scene->cam.point[_X] -= 1 * z_dir;
	else if (keysym == 65431)
		scene->cam.point[_Z] += 1 * z_dir;
	else if (keysym == 65433)
		scene->cam.point[_Z] -= 1 * z_dir;
}

void	k_directional_controls(int keysym, t_mlx *mlx)
{
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
