/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_object.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akretov <akretov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 18:52:10 by akretov           #+#    #+#             */
/*   Updated: 2024/10/14 18:52:16 by akretov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	init_object_selection(t_scene *scene)
{
	int	y;
	int	x;

	x = 0;
	y = 0;
	while (y < RES_H)
	{
		while (x < RES_W)
			scene->screen_object[y][x++] = NULL;
		x = 0;
		y++;
	}
	scene->selected = NULL;
}
