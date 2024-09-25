/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 13:57:37 by jcummins          #+#    #+#             */
/*   Updated: 2024/09/20 16:44:00 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	print_meta(t_scene *scene)
{
	if (!scene->valid)
		printf(KRED "*** INVALID SCENE - WILL NOT RUN ***");
	else
		printf(KGRN);
	printf("\nFile %d (%s) input:\n", scene->id, scene->fname);
	printf("Scene %d: spheres: %d, planes: %d, cylinders: %d\n" KDEF, \
			scene->id, scene->n_spheres, \
			scene->n_planes, scene->n_cylinders);
}

void	print_scene(t_scene *scene)
{
	print_meta(scene);
	print_uniqs(scene);
	print_shapes(scene);
}

void	print_scenes(t_rt *rt)
{
	int	i;

	i = 0;
	while (i < rt->n_scenes)
		print_scene(rt->scenes[i++]);
}
