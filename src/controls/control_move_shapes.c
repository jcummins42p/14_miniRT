/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_move_shapes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 12:18:20 by jcummins          #+#    #+#             */
/*   Updated: 2024/10/17 20:13:16 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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
	else
		k_rotate(scene, keysym);
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
