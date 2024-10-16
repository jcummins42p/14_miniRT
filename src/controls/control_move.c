/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_move.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 12:18:20 by jcummins          #+#    #+#             */
/*   Updated: 2024/10/13 18:40:21 by akretov          ###   ########.fr       */
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

void	k_move_cylinder(int keysym, t_scene *scene)
{
	float		z_dir;
	t_cylinder	*cylinder;

	cylinder = scene->selected;
	z_dir = scene->cam.dir[_Z];
	if (keysym == XK_KP_3)
		cylinder->center[_Y] += 1;
	else if (keysym == XK_KP_1)
		cylinder->center[_Y] -= 1;
	else if (keysym == XK_KP_6)
		cylinder->center[_X] += 1 * z_dir;
	else if (keysym == XK_KP_4)
		cylinder->center[_X] -= 1 * z_dir;
	else if (keysym == XK_KP_8)
		cylinder->center[_Z] += 1 * z_dir;
	else if (keysym == XK_KP_2)
		cylinder->center[_Z] -= 1 * z_dir;
	else if (keysym == XK_KP_9)
		cylinder->diamtr += 0.05;
	else if (keysym == XK_KP_7)
		cylinder->diamtr -= 0.05;
}
void k_move_camera(int keysym, t_scene *scene)
{
	t_vec3 move_dir;
	t_camera *cam = &scene->cam;

	if (keysym == XK_KP_3)		// Move up
		cam->point[_Y] += 1;
	else if (keysym == XK_KP_1)   // Move down
		cam->point[_Y] -= 1;
	else if (keysym == XK_KP_6)   // Move right
	{
		vec3_set_a(move_dir, cam->right);
		cam->point[_X] += move_dir[_X];
		cam->point[_Y] += move_dir[_Y];
		cam->point[_Z] += move_dir[_Z];
	}
	else if (keysym == XK_KP_4)   // Move left
	{
		vec3_set_a(move_dir, cam->right);
		vec3_a_to_b(cam->point, move_dir, cam->point);
	}
	else if (keysym == XK_KP_8)   // Move forward
	{
		vec3_set_a(move_dir, cam->dir);
		cam->point[_X] += move_dir[_X];
		cam->point[_Y] += move_dir[_Y];
		cam->point[_Z] += move_dir[_Z];
	}
	else if (keysym == XK_KP_2)   // Move backward
	{
		vec3_set_a(move_dir, cam->dir);
		vec3_a_to_b(cam->point, move_dir, cam->point);
	}
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
	else if (mlx->rt->scenes[mlx->rt->curr_scene]->sel_type == SEL_CYLINDER_CAP 
			|| mlx->rt->scenes[mlx->rt->curr_scene]->sel_type == SEL_CYLINDER_SIDE)
		k_move_cylinder(keysym, mlx->rt->scenes[mlx->rt->curr_scene]);
	else if (mlx->rt->scenes[mlx->rt->curr_scene]->sel_type == SEL_CAM)
		k_move_camera(keysym, mlx->rt->scenes[mlx->rt->curr_scene]);
	else if (mlx->rt->scenes[mlx->rt->curr_scene]->sel_type == SEL_AMBIENT)
		k_control_ambient(keysym, mlx->rt->scenes[mlx->rt->curr_scene]);
	else if (mlx->rt->scenes[mlx->rt->curr_scene]->sel_type == SEL_LIGHT_VALS)
		k_control_light(keysym, mlx->rt->scenes[mlx->rt->curr_scene]);
	render_scene(mlx, mlx->rt->scenes[mlx->rt->curr_scene]);
}
