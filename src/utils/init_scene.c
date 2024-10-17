/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 20:38:24 by jcummins          #+#    #+#             */
/*   Updated: 2024/10/17 19:11:53 by jcummins         ###   ########.fr       */
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

void	init_scene_shape_data(t_scene *scene)
{
	scene->n_cylinders = 0;
	scene->n_planes = 0;
	scene->n_spheres = 0;
	scene->cyls = NULL;
	scene->plns = NULL;
	scene->sphs = NULL;
}

void	init_scene_vectors(t_scene *scene)
{
	set_vec3(scene->cam.point, "-42,0,42");
	set_vec3(scene->cam.dir, "-42,0,42");
	set_vec3(scene->light.point, "-42,42,0");
	set_vec3(scene->axis[0], "1,0,0");
	set_vec3(scene->axis[1], "0,1,0");
	set_vec3(scene->axis[2], "0,0,1");
}

int	init_scene(t_scene *scene, char *filename, int id)
{
	init_object_selection(scene);
	init_scene_shape_data(scene);
	scene->fname = ft_strdup(filename);
	if (!scene->fname)
		return (1);
	scene->img = malloc(sizeof(t_img));
	if (!scene->img)
		return (1);
	scene->id = id;
	scene->valid = true;
	scene->sky = 0x424242;
	scene->amb.lock = false;
	scene->amb.lum = 0.42;
	scene->amb.hue = 0x424242;
	scene->cam.lock = false;
	scene->cam.fov = 42;
	scene->light.lock = false;
	scene->light.lum = 0.42;
	scene->light.hue = 0x424242;
	return (0);
}

int	init_scenes(t_rt *rt, char **argv)
{
	int	i;

	i = -1;
	while (++i < rt->n_scenes)
	{
		if (init_scene(rt->scenes[i], argv[i + 1], i))
			return (1);
	}
	return (0);
}
