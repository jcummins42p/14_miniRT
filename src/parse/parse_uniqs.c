/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_uniqs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 20:47:58 by jcummins          #+#    #+#             */
/*   Updated: 2024/09/27 15:05:27 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

//	These elements of need to be parsed once and only once! Hence the lock
void	parse_ambient(char *input, t_scene *scene)
{
	char	**items;

	if (scene->amb.lock++)
		scene->valid = false;
	if (!input || !*input)
		printf("Error: NULL string passed to parse_ambient, init to default\n");
	else
	{
		items = ft_split(input, ' ');
		scene->amb.lum = ft_atof(items[1]);
		scene->amb.hue = set_color(items[2]);
		scene->sky = scene->amb.hue;
		ft_free_string_list(items);
	}
}

void	orient_camera(t_camera *cam)
{
	t_vec3	world_up;

	set_vec3(world_up, "0,1,0");
	cross_product(cam->right, world_up, cam->dir);
	vec3_normalize(cam->right, cam->right);
	cross_product(cam->up, cam->dir, cam->right);
	vec3_normalize(cam->up, cam->up);
}

void	parse_camera(char *input, t_scene *scene)
{
	char	**items;

	if (scene->cam.lock++)
		scene->valid = false;
	if (!input || !*input)
		printf("Error: NULL string passed to parse_camera, init to default\n");
	else
	{
		items = ft_split(input, ' ');
		set_vec3(scene->cam.point, items[1]);
		scene->cam.fov = ft_atoi(items[3]);
		if (set_unit_vec3(scene->cam.dir, items[2]))
			scene->valid = false;
		ft_free_string_list(items);
		vec3_set_a(scene->cam.point_def, scene->cam.point);
		vec3_set_a(scene->cam.dir_def, scene->cam.dir);
		orient_camera(&scene->cam);
	}
}

void	parse_light(char *input, t_scene *scene)
{
	char		**items;

	if (scene->light.lock++)
		scene->valid = false;
	if (!input || !*input)
		printf("Error: NULL string passed to parse_light, init to default\n");
	else
	{
		items = ft_split(input, ' ');
		set_vec3(scene->light.point, items[1]);
		scene->light.lum = ft_atof(items[2]);
		scene->light.hue = set_color(items[3]);
		ft_free_string_list(items);
	}
}
