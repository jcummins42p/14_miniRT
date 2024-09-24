/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_uniqs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 20:47:58 by jcummins          #+#    #+#             */
/*   Updated: 2024/09/24 14:37:34 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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

void	parse_camera(char *input, t_scene *scene)
{
	char		**items;
	t_vector	world_up;

	set_vector(world_up, "0,1,0");
	if (scene->cam.lock++)
		scene->valid = false;
	if (!input || !*input)
		printf("Error: NULL string passed to parse_camera, init to default\n");
	else
	{
		items = ft_split(input, ' ');
		set_vector(scene->cam.point, items[1]);
		if (set_unit_vector(scene->cam.dir, items[2]))
			scene->valid = false;
		scene->cam.fov = ft_atoi(items[3]);
		ft_free_string_list(items);
		cross_product(scene->cam.right, world_up, scene->cam.dir);
		vector_normalize(scene->cam.right, scene->cam.right);
		cross_product(scene->cam.up, scene->cam.dir, scene->cam.right);
		vector_normalize(scene->cam.up, scene->cam.up);
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
		set_vector(scene->light.point, items[1]);
		scene->light.lum = ft_atof(items[2]);
		scene->light.hue = set_color(items[3]);
		ft_free_string_list(items);
	}
}
