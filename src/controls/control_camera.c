/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_camera.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 17:22:40 by jcummins          #+#    #+#             */
/*   Updated: 2024/10/18 16:16:43 by akretov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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
