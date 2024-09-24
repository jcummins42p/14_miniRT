/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_alloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 20:24:31 by jcummins          #+#    #+#             */
/*   Updated: 2024/09/24 20:30:13 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	alloc_shapes(t_rt *rt)
{
	t_scene	**scenes;
	int		i;

	scenes = rt->scenes;
	i = -1;
	while (++i < rt->n_scenes)
	{
		scenes[i]->sphs = malloc(sizeof(t_sphere) * scenes[i]->n_spheres);
		scenes[i]->plns = malloc(sizeof(t_plane) * scenes[i]->n_planes);
		scenes[i]->cyls = malloc(sizeof(t_cylinder) * scenes[i]->n_cylinders);
		if (scenes[i]->sphs == NULL
			|| scenes[i]->plns == NULL
			|| scenes[i]->cyls == NULL)
		{
			printf("Error: failure to malloc shapes");
			dealloc_shapes(scenes, i);
			return (1);
		}
		init_spheres(scenes[i]);
		init_planes(scenes[i]);
		init_cylinders(scenes[i]);
	}
	return (0);
}

t_scene	**alloc_scenes(int n_scenes)
{
	t_scene	**scenes;
	int		i;

	i = 0;
	scenes = malloc(n_scenes * sizeof(t_scene *));
	if (!scenes)
		return (NULL);
	while (i < n_scenes)
	{
		scenes[i] = malloc(sizeof(t_scene));
		if (!scenes[i])
		{
			while (i-- > 0)
				free(scenes[i]);
			free(scenes);
			return (NULL);
		}
		i++;
	}
	return (scenes);
}
