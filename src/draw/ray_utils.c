/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 15:38:11 by jcummins          #+#    #+#             */
/*   Updated: 2024/10/01 15:47:08 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

//	sets a 2d normalized device vector for that co-ordinate's relative position
//	on the virtual screen between -1,-1 (top left) and 1,1 (bottom right) going
//	through 0,0 (center of screen)
void	norm_device_coords(t_vec2 ndc, int x, int y)
{
	ndc[_X] = ((2.0 * x) / RES_W) - 1.0;
	ndc[_Y] = 1.0 - ((2.0 * y) / RES_H);
}

//	uses the ndc vector to generate co-ordinate for that x,y on the virtual
//	screen. The relationship between fov (theta) and distance to image plane:
//	tan(theta/2) = ymax / d
//	where ymax it the distance from the middle of the screen to the top
void	project_viewport(t_vec2 project, t_vec2 ndc, int fov, float aspect)
{
	project[_X] = (ndc[_X] * aspect * fl_abs(tan(fov / 2.0)));
	project[_Y] = (ndc[_Y] * fl_abs(tan(fov / 2.0)));
}

void	set_ray_direction(t_vec3 dir, t_vec2 plane, t_camera cam)
{
	dir[_X] = cam.dir[_X] + cam.right[_X] * plane[_X] + cam.up[_X] * plane[_Y];
	dir[_Y] = cam.dir[_Y] + cam.right[_Y] * plane[_X] + cam.up[_Y] * plane[_Y];
	dir[_Z] = cam.dir[_Z] + cam.right[_Z] * plane[_X] + cam.up[_Z] * plane[_Y];
}
