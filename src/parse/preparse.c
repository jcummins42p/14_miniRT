/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 20:04:53 by jcummins          #+#    #+#             */
/*   Updated: 2024/09/19 20:09:26 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	preparse_select(char *line, t_scene *scene)
{
	if (!ft_strncmp(line, "sp", 2))
		scene->n_spheres++;
	else if (!ft_strncmp(line, "pl", 2))
		scene->n_planes++;
	else if (!ft_strncmp(line, "cy", 2))
		scene->n_cylinders++;
}

void	preparse(int fd[], t_scene **scenes, int n_scenes)
{
	char	*line;
	int		i;

	i = -1;
	printf("Pre-parsing input to set number of shapes\n");
	while (++i < n_scenes)
	{
		line = NULL;
		line = get_next_line(fd[i]);
		while (line)
		{
			preparse_select(line, scenes[i]);
			free (line);
			line = get_next_line(fd[i]);
		}
	}
	while (--i >= 0)
		close (fd[i]);
}
