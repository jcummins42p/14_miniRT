/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_move_cylinder.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 18:56:43 by akretov           #+#    #+#             */
/*   Updated: 2024/10/17 20:08:00 by akretov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	move_cylinder(t_cylinder *cylinder, int keysym, float z_dir)
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

void	resize_cylinder(t_cylinder *cylinder, int keysym)
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

void	k_move_cylinder(int keysym, t_scene *scene)
{
	float		z_dir;
	t_cylinder	*cylinder;

	cylinder = scene->selected;
	z_dir = scene->cam.dir[_Z];
	move_cylinder(cylinder, keysym, z_dir);
	resize_cylinder(cylinder, keysym);
	k_rotate(scene, keysym);
}
