/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 09:57:21 by jcummins          #+#    #+#             */
/*   Updated: 2024/09/19 18:46:19 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	set_colors(char *input) // assumes csv RGB
{
	char	**items;
	int		color;

	color = 0;
	items = NULL;
	if (!input || !*input)
		return (0);
	items = ft_split(input, ',');
	color += ft_atoi(items[0]) << 16;
	color += ft_atoi(items[1]) << 8;
	color += ft_atoi(items[2]);
	ft_free_string_list(items);
	return (color);
}

void	zero_vector(t_vector vec)
{
	int	i;

	i = 0;
	while (i < 3)
		vec[i++] = 0.0;
}

void	print_vector(char *message, t_vector vec)
{
	printf("%s", message);
	printf("%.2f,%.2f,%.2f", vec[0], vec[1], vec[2]);
}

void	set_vector(t_vector vec, char *input)
{
	char		**items;
	int			i;

	i = -1;
	items = NULL;
	if (!input || !*input)
		return ;
	items = ft_split(input, ',');
	while (++i < 3)
		vec[i] = ft_atof(items[i]);
	ft_free_string_list(items);
}

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

void	parse_plane(char *input, t_scene *scene)
{
	char		**items;

	if (!input || !*input)
		printf("Error: NULL string passed to parse_plane, init to default\n");
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

void	parse_sphere(char *input, t_scene *scene)
{
	(void) scene;
	(void) input;
	printf("\t->Unimplemented parse SPHERE\n");
}

void	parse_cylinder(char *input, t_scene *scene)
{
	(void) scene;
	(void) input;
	printf("\t->Unimplemented parse CYLINDER\n");
}

void	parse_select(char *line, t_scene *scene)
{
	if (!ft_strncmp(line, "A", 1))
		parse_ambient(line, scene);
	else if (!ft_strncmp(line, "C", 1))
		parse_camera(line, scene);
	else if (!ft_strncmp(line, "L", 1))
		parse_light(line, scene);
	else if (!ft_strncmp(line, "sp", 2))
		parse_sphere(line, scene);
	else if (!ft_strncmp(line, "pl", 2))
		parse_plane(line, scene);
	else if (!ft_strncmp(line, "cy", 2))
		parse_cylinder(line, scene);
	else if (*line)
		printf("\t*** Unrecognised parse type warning ***\n");
}

void	parse_file(int fd, t_scene *scene)
{
	char	*line;

	(void) scene;
	line = NULL;
	line = get_next_line(fd);
	while (line)
	{
		parse_select(line, scene);
		free (line);
		line = get_next_line(fd);
	}
}

void	parse(int *fd, int argc, t_scene **scenes)
{
	int	i;

	i = -1;
	while (++i < argc - 1)
	{
		printf("\nFile %d (%s) input:\n", i, scenes[i]->fname);
		printf("Scene %d: spheres: %d, planes: %d, cylinders: %d\n", \
				scenes[i]->id, scenes[i]->n_spheres, \
				scenes[i]->n_planes, scenes[i]->n_cylinders);
		parse_file(fd[i], scenes[i]);
	}
}
