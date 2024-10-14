/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_move_camera.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 20:24:27 by akretov           #+#    #+#             */
/*   Updated: 2024/10/14 20:28:36 by akretov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	k_move_camera(int keysym, t_scene *scene)
{
	t_vec3		move_dir;
	t_camera	*cam;

	cam = &scene->cam;
	if (keysym == XK_KP_3)
		cam->point[_Y] += 1;
	else if (keysym == XK_KP_1)
		cam->point[_Y] -= 1;
	else if (keysym == XK_KP_6)
	{
		vec3_set_a(move_dir, cam->right);
		vec3_invert(move_dir);
		vec3_a_to_b(cam->point, move_dir, cam->point);
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
		vec3_a_to_b(cam->point, move_dir, cam->point);
	}
	else if (keysym == XK_KP_2)
	{
		vec3_set_a(move_dir, cam->dir);
		vec3_a_to_b(cam->point, move_dir, cam->point);
	}
	else if (keysym == XK_KP_7 || keysym == XK_KP_9)
		k_cam_pan(keysym, &scene->cam);
}
