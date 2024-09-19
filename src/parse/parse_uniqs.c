/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_uniqs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 20:47:58 by jcummins          #+#    #+#             */
/*   Updated: 2024/09/19 20:55:43 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	parse_ambient(char *input, t_scene *scene)
{
	char	**items;

	if (scene->amb.lock++)
	{
		scene->valid = false;
		printf("Error : file contains multiple ambient definitions\n");
	}
	if (!input || !*input)
		printf("Error: NULL string passed to parse_ambient, init to default\n");
	else
	{
		items = ft_split(input, ' ');
		scene->amb.lum = ft_atof(items[1]);
		scene->amb.hue = set_colors(items[2]);
		ft_free_string_list(items);
		if (DEBUGMODE && scene->valid)
			printf("->Ambient:\tluminosity:\t%f\t\thue:\t\t%d\n", \
					scene->amb.lum, scene->amb.hue);
	}
}

void	parse_camera(char *input, t_scene *scene)
{
	char		**items;

	if (scene->cam.lock++)
	{
		scene->valid = false;
		printf("Error: file contains multiple camera definitions\n");
	}
	if (!input || !*input)
		printf("Error: NULL string passed to parse_camera, init to default\n");
	else
	{
		items = ft_split(input, ' ');
		set_vector(scene->cam.point, items[1]);
		set_vector(scene->cam.dir, items[2]);
		scene->cam.fov = ft_atoi(items[3]);
		ft_free_string_list(items);
		if (DEBUGMODE && scene->valid)
		{
			printf("->Camera:");
			print_vector("\tviewpoint:\t", scene->cam.point);
			print_vector("\torientation:\t", scene->cam.dir);
			printf("\tfov:\t%d\n", scene->cam.fov);
		}
	}
}

void	parse_light(char *input, t_scene *scene)
{
	char		**items;

	if (scene->light.lock++)
	{
		scene->valid = false;
		exit_error("Error: multiple light definitions\n", ERR_PARSE);
	}
	if (!input || !*input)
		printf("Error: NULL string passed to parse_light, init to default\n");
	else
	{
		items = ft_split(input, ' ');
		set_vector(scene->light.point, items[1]);
		scene->light.lum = ft_atof(items[2]);
		scene->light.hue = set_colors(items[3]);
		ft_free_string_list(items);
		if (DEBUGMODE && scene->valid)
		{
			printf("->Light:");
			print_vector("\tpoint:\t\t", scene->light.point);
			printf("\tbrightness:\t%.2f", scene->light.lum);
			printf("\t\thue:\t%d\n", scene->light.hue);
		}
	}
}
