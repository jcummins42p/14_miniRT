/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shapes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:39:12 by jcummins          #+#    #+#             */
/*   Updated: 2024/10/17 16:39:22 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	init_spheres(t_scene *scene)
{
	int	i;

	i = -1;
	while (++i < scene->n_spheres)
	{
		scene->sphs[i].id = -1;
		set_vec3(scene->sphs[i].center, "0,0,42");
		scene->sphs[i].diamtr = 42.0;
		scene->sphs[i].color = 0x424242;
	}
}

void	init_planes(t_scene *scene)
{
	int	i;

	i = -1;
	while (++i < scene->n_planes)
	{
		scene->plns[i].id = -1;
		set_vec3(scene->plns[i].anch, "0,0,-42");
		set_vec3(scene->plns[i].norm, "0,0,0.42");
		scene->plns[i].color = 0x424242;
	}
}

void	init_cylinders(t_scene *scene)
{
	int	i;

	i = -1;
	while (++i < scene->n_cylinders)
	{
		scene->cyls[i].id = -1;
		set_vec3(scene->cyls[i].center, "0,0,42");
		set_vec3(scene->cyls[i].axis, "0,0,0.42");
		scene->cyls[i].diamtr = 0.42;
		scene->cyls[i].height = 0.42;
		scene->cyls[i].color = 0x424242;
	}
}
