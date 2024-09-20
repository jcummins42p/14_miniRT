/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_uniqs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 20:47:58 by jcummins          #+#    #+#             */
/*   Updated: 2024/09/20 15:19:40 by jcummins         ###   ########.fr       */
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
		scene->amb.hue = set_colors(items[2]);
		ft_free_string_list(items);
	}
}

void	parse_camera(char *input, t_scene *scene)
{
	char		**items;

	if (scene->cam.lock++)
		scene->valid = false;
	if (!input || !*input)
		printf("Error: NULL string passed to parse_camera, init to default\n");
	else
	{
		items = ft_split(input, ' ');
		set_vector(scene->cam.point, items[1]);
		set_vector(scene->cam.dir, items[2]);
		scene->cam.fov = ft_atoi(items[3]);
		ft_free_string_list(items);
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
		scene->light.hue = set_colors(items[3]);
		ft_free_string_list(items);
	}
}
