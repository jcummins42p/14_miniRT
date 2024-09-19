/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 09:57:21 by jcummins          #+#    #+#             */
/*   Updated: 2024/09/19 14:35:16 by jcummins         ###   ########.fr       */
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

void	parse_ambient(char *input, t_scene *scene)
{
	static int	lock;
	char	**items;

	if (lock++)
		exit_error("Error :multiple ambient definitions", ERR_PARSE);
	items = ft_split(input, ' ');
	scene->amb.lum = ft_atof(items[1]);
	scene->amb.hue = set_colors(items[2]);
	printf("ambient: luminosity: %f\thue: %d\n", scene->amb.lum, scene->amb.hue);
}

void	parse_camera(char *input, t_scene *scene)
{
	(void) scene;
	(void) input;
	printf("\t->Unimplemented parse CAMERA\n");
}

void	parse_light(char *input, t_scene *scene)
{
	(void) scene;
	(void) input;
	printf("\t->Unimplemented parse LIGHT\n");
}

void	parse_plane(char *input, t_scene *scene)
{
	(void) scene;
	(void) input;
	printf("\t->Unimplemented parse PLANE\n");
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
		line = get_next_line(fd);
	}
}

void	parse(int *fd, int argc, t_scene **scenes)
{
	int	i;

	i = -1;
	printf("Parsing input\n");
	while (++i < argc - 1)
		parse_file(fd[i], scenes[i]);
}
