/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 09:57:21 by jcummins          #+#    #+#             */
/*   Updated: 2024/10/18 16:16:43 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	parse_select(char *line, t_scene *scene)
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

static void	parse_file(int fd, t_scene *scene)
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
	if (!scene->amb.lock || !scene->cam.lock || !scene->light.lock
		|| !(scene->n_cylinders + scene->n_planes + scene->n_spheres))
		scene->valid = false;
}

void	parse(t_rt *rt)
{
	int	i;

	i = -1;
	while (++i < rt->n_scenes)
		parse_file(rt->fd[i], rt->scenes[i]);
}
