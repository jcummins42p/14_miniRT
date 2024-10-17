/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_move_cylinder.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 18:56:43 by akretov           #+#    #+#             */
/*   Updated: 2024/10/17 19:20:10 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void move_cylinder(t_cylinder *cylinder, int keysym, float z_dir)
{
	if (keysym == XK_KP_3)
		cylinder->center[_Y] += 1.0f;
	else if (keysym == XK_KP_1)
		cylinder->center[_Y] -= 1.0f;
	else if (keysym == XK_KP_6)
		cylinder->center[_X] += 1.0f * z_dir;
	else if (keysym == XK_KP_4)
		cylinder->center[_X] -= 1.0f * z_dir;
	else if (keysym == XK_KP_8)
		cylinder->center[_Z] += 1.0f * z_dir;
	else if (keysym == XK_KP_2)
		cylinder->center[_Z] -= 1.0f * z_dir;
}

static void resize_cylinder(t_cylinder *cylinder, int keysym)
{
	if (keysym == XK_KP_9)
		cylinder->diamtr += 0.05f;
	else if (keysym == XK_KP_7)
		cylinder->diamtr -= 0.05f;
	else if (keysym == XK_KP_A)
		cylinder->height += 0.05f;
	else if (keysym == XK_KP_D)
		cylinder->height -= 0.05f;

	cylinder->radius = cylinder->diamtr / 2;
}

static void rotate_cylinder(t_scene *scene, t_cylinder *cylinder, int keysym)
{
	t_quaternion q;
	/*t_vec3 y_axis = {0, 1, 0};*/
	/*t_vec3 x_axis = {1, 0, 0};*/

	if (keysym == XK_KP_Q)
		q = axis_angle_to_quaternion(scene->axis[1], 0.1f);
	else if (keysym == XK_KP_E)
		q = axis_angle_to_quaternion(scene->axis[1], -0.1f);
	else if (keysym == XK_KP_W)
		q = axis_angle_to_quaternion(scene->axis[0], -0.1f);
	else if (keysym == XK_KP_S)
		q = axis_angle_to_quaternion(scene->axis[0], 0.1f);
	else
		return ;
	rotate_vector_by_quaternion(cylinder->axis, q);
}

void k_move_cylinder(int keysym, t_scene *scene)
{
	float		z_dir;
	t_cylinder	*cylinder;

	cylinder = scene->selected;
	z_dir = scene->cam.dir[_Z];
	move_cylinder(cylinder, keysym, z_dir);
	resize_cylinder(cylinder, keysym);
	rotate_cylinder(scene, cylinder, keysym);
}
