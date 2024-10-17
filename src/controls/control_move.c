/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_move.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 12:18:20 by jcummins          #+#    #+#             */
/*   Updated: 2024/10/17 19:59:11 by jcummins         ###   ########.fr       */
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

void	rotate_quaternion(t_scene *scene, int axis, float incr)
{
	t_quaternion q;

	q = axis_angle_to_quaternion(scene->axis[axis], incr);
	if (scene->sel_type == SEL_CAM)
		rotate_vector_by_quaternion(scene->cam.dir, q);
	else if (scene->sel_type == SEL_PLANE)
		rotate_vector_by_quaternion(((t_plane *)scene->selected)->norm, q);
	else if (scene->sel_type == SEL_CYLINDER_CAP
			|| scene->sel_type == SEL_CYLINDER_SIDE)
		rotate_vector_by_quaternion(((t_cylinder *)scene->selected)->axis, q);
}

void	k_rotate(t_scene *scene, int keysym)
{
	if (keysym == XK_KP_7 || keysym == XK_KP_9)
		k_cam_pan(keysym, &scene->cam);
	else if (keysym == XK_KP_Q)
		rotate_quaternion(scene, 1, -0.1);
	else if (keysym == XK_KP_E)
		rotate_quaternion(scene, 1, 0.1);
	else if (keysym == XK_KP_W)
		rotate_quaternion(scene, 0, -0.1);
	else if (keysym == XK_KP_S)
		rotate_quaternion(scene, 0, 0.1);
	else if (keysym == XK_KP_A)
		rotate_quaternion(scene, 2, -0.1);
	else if (keysym == XK_KP_D)
		rotate_quaternion(scene, 2, 0.1);
}

void	k_move_camera(int keysym, t_scene *scene)
{
	t_vec3		move_dir;
	t_camera 	*cam;

	cam = &scene->cam;
	if (keysym == XK_KP_3)
		cam->point[_Y] += 1;
	else if (keysym == XK_KP_1)
		cam->point[_Y] -= 1;
	else if (keysym == XK_KP_6)
	{
		vec3_set_a(move_dir, cam->right);
		vec3_invert(move_dir);
		vec3_a_to_b(cam->point, move_dir,cam->point);
	}
	else if (keysym == XK_KP_4)
	{
		vec3_set_a(move_dir, cam->right);
		vec3_a_to_b(cam->point, move_dir, cam->point);
	}
	else if (keysym == XK_KP_8)
	{
		vec3_set_a(move_dir, cam->dir);
		vec3_invert(move_dir);
		vec3_a_to_b(cam->point, move_dir,cam->point);
	}
	else if (keysym == XK_KP_2)
	{
		vec3_set_a(move_dir, cam->dir);
		vec3_a_to_b(cam->point, move_dir, cam->point);
	}
	else
		k_rotate(scene, keysym);
	orient_camera(&scene->cam);
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
