/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 14:20:10 by jcummins          #+#    #+#             */
/*   Updated: 2024/10/17 14:20:33 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	highlight_selected(t_scene *scene, int x, int y, int radius)
{
	if (!scene->selected || scene->screen_object[y][x] == scene->selected)
		return ;
	if (x + radius >= RES_W
		|| y + radius >= RES_H
		|| x - radius <= 0
		|| y - radius <= 0)
		return ;
	if (scene->screen_object[y + radius][x + radius] == scene->selected
		|| scene->screen_object[y - radius][x + radius] == scene->selected
		|| scene->screen_object[y + radius][x - radius] == scene->selected
		|| scene->screen_object[y - radius][x - radius] == scene->selected)
		pixel_put_img(scene->img, x, y, XCOL_WHT);
}

void	post_process(t_scene *scene)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < RES_H)
	{
		x = 0;
		while (x < RES_W)
		{
			highlight_selected(scene, x++, y, HIGHLIGHT_RAD);
		}
		y++;
	}
}
