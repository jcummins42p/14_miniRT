/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 20:38:24 by jcummins          #+#    #+#             */
/*   Updated: 2024/09/19 20:43:58 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	init_scene(t_scene *scene, char *filename, int id)
{
	scene->fname = ft_strdup(filename);
	scene->id = id;
	scene->valid = true;
	scene->n_cylinders = 0;
	scene->n_planes = 0;
	scene->n_spheres = 0;
	scene->sky = 0x420000;
	scene->amb.lock = false;
	scene->amb.lum = 0.2;
	scene->amb.hue = 0xFFFFFF;
	scene->cam.lock = false;
	set_vector(scene->cam.point, "-50,0,20");
	set_vector(scene->cam.dir, "-50,0,20");
	scene->cam.fov = 70;
	scene->light.lock = false;
	set_vector(scene->light.point, "-40,50,0");
	scene->light.lum = 0.6;
	scene->light.hue = 0x0A00FF;
	scene->cyls = NULL;
	scene->plns = NULL;
	scene->sphs = NULL;
}

void	init_scenes(t_scene **scenes, char **argv, int n_scenes)
{
	int	i;

	i = -1;
	while (++i < n_scenes)
		init_scene(scenes[i], argv[i + 1], i);
}

void	init_spheres(t_scene *scene)
{
	int	i;

	i = -1;
	while (++i < scene->n_spheres)
	{
		scene->sphs[i].id = 0;
		set_vector(scene->sphs[i].center, "0,0,20");
		scene->sphs[i].diamtr = 20.0;
		scene->sphs[i].color = 0x424242;
	}
}

void	init_planes(t_scene *scene)
{
	int	i;

	i = -1;
	while (++i < scene->n_planes)
	{
		scene->plns[i].id = 0;
		set_vector(scene->plns[i].anch, "0,0,-10");
		set_vector(scene->plns[i].norm, "0,0,1");
		scene->plns[i].color = 0x424242;
	}
}

void	init_cylinders(t_scene *scene)
{
	int	i;

	i = -1;
	while (++i < scene->n_cylinders)
	{
		scene->cyls[i].id = 0;
		set_vector(scene->cyls[i].center, "0,0,20");
		set_vector(scene->cyls[i].axis, "0,0,20");
		scene->cyls[i].diamtr = 14.2;
		scene->cyls[i].height = 21.42;
		scene->cyls[i].color = 0x424242;
	}
}
