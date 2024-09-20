/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 20:04:53 by jcummins          #+#    #+#             */
/*   Updated: 2024/09/20 16:28:04 by jcummins         ###   ########.fr       */
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

void	preparse(t_rt *rt)
{
	char	*line;
	int		i;

	i = -1;
	while (++i < rt->n_scenes)
	{
		line = NULL;
		line = get_next_line(rt->fd[i]);
		while (line)
		{
			preparse_select(line, rt->scenes[i]);
			free (line);
			line = get_next_line(rt->fd[i]);
		}
	}
	while (--i >= 0)
		close (rt->fd[i]);
}
