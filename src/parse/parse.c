/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 09:57:21 by jcummins          #+#    #+#             */
/*   Updated: 2024/09/19 20:50:58 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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
}

void	parse_file(int fd, t_scene *scene)
{
	char	*line;

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
		printf("\n\nFile %d (%s) input:\n", i, scenes[i]->fname);
		printf("Scene %d: spheres: %d, planes: %d, cylinders: %d\n", \
				scenes[i]->id, scenes[i]->n_spheres, \
				scenes[i]->n_planes, scenes[i]->n_cylinders);
		parse_file(fd[i], scenes[i]);
	}
}
