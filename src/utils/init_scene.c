/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 20:38:24 by jcummins          #+#    #+#             */
/*   Updated: 2024/09/30 15:38:45 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	init_object_selection(t_scene *scene)
{
	int	y;
	int x;

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

void	init_scene(t_scene *scene, char *filename, int id)
{
	init_object_selection(scene);
	scene->fname = ft_strdup(filename);
	scene->img = malloc(sizeof(t_img));
	scene->id = id;
	scene->valid = true;
	scene->rend.scan = false;
	scene->rend.res = RES_FULL;
	scene->n_cylinders = 0;
	scene->n_planes = 0;
	scene->n_spheres = 0;
	scene->sky = 0x424242;
	scene->amb.lock = false;
	scene->amb.lum = 0.42;
	scene->amb.hue = 0x424242;
	scene->cam.lock = false;
	set_vec3(scene->cam.point, "-42,0,42");
	set_vec3(scene->cam.dir, "-42,0,42");
	scene->cam.fov = 42;
	scene->light.lock = false;
	set_vec3(scene->light.point, "-42,42,0");
	scene->light.lum = 0.42;
	scene->light.hue = 0x424242;
	scene->cyls = NULL;
	scene->plns = NULL;
	scene->sphs = NULL;
}

void	init_scenes(t_rt *rt, char **argv)
{
	int	i;

	i = -1;
	while (++i < rt->n_scenes)
		init_scene(rt->scenes[i], argv[i + 1], i);
}

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
